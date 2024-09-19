#pragma once
#include "Utilities.h"
#include "HandlerWaltan.h"
#include "HWBoxCollider.h"
#include "HWSphereCollider.h"
#include "HWCapsuleCollider.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		ColliderWaltanの定義ファイル
*/


/**
 * @class	ColliderWaltan
 * @brief   毎Fコライダーコンポーネントのあたり判定を監視し、条件に応じたハンドラーを呼び出す
 */
class CollisionWaltan
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HandlerWaltan;
    friend class HWBoxCollider;
    friend class HWSphereCollider;
    friend class HWCapsuleCollider;

    // コリジョンチェックに使う構造体

    /**
    * @struct	OBB
    * @brief	立方体の当たり判定
    */
    struct OBB {
        //! OBBの中心座標
        VECTOR center;      
        //! 各軸ベクトル（正規化済み）
        VECTOR axis[3];     
        //! 各軸方向のハーフサイズ
        float halfSize[3];  
    };

private:

    /*     メンバ変数     */

    /**
     * @brief		インスタンス化されているコライダー
     * @History		24/09/17 作成(Suzuki N)
     */
    std::vector<HWCollider*> ColVec;


private:

    /*     メソッド     */

    /**
     * @brief       インスタンスを取得する静的メソッド
     * @detail      初めの一回だけインスタンスを生成する
     * @return      CollisionWaltan& シングルトンインスタンス
     * @author      Suzuki N
     * @date        24/07/19
     */
    static CollisionWaltan& Instance()
    {
        // シングルトンインスタンスを生成
        static CollisionWaltan instance;
        return instance;
    }

    //インスタンスのコピー禁止
    //デフォルトのコピーコンストラクタを削除
    CollisionWaltan(const CollisionWaltan&) = delete;
    //デフォルトのコピー代入演算子も削除
    CollisionWaltan& operator=(const CollisionWaltan&) = delete;

    /**
     * @brief       コンストラクタ
     * @author      Suzuki N
     * @date        24/07/19
     */
    CollisionWaltan();

    /**
     * @brief       デストラクタ
     * @author      Suzuki N
     * @date        24/07/19
     */
    ~CollisionWaltan();

    /**
      * @brief       各コンポーネントのUpdateメソッドを全て呼び出す
      * @author      Suzuki N
      * @date        24/08/22
      */
    void Update();

    /**
     * @brief       登録されているコライダー情報を削除する
     * @param[in]   HWCollider* 削除するコライダー情報
     * @author      Suzuki N
     * @date        24/09/17
     */
    void UnRegister(HWCollider* _collider);

    /**
      * @brief       要素1 がBoxColliderの場合のコリジョンチェック
      * @param[in]   HWBoxCollider* あたり判定の重なりを見る立方体型Collider情報1
      * @param[in]   HWCollider*    あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Box(HWBoxCollider* _boxCol1, HWCollider* _col2);

    /**
      * @brief       要素1 がSphereColliderの場合のコリジョンチェック
      * @param[in]   HWSphereCollider*   あたり判定の重なりを見る球体型Collider情報1
      * @param[in]   HWCollider*         あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Sphere(HWSphereCollider* _col1, HWCollider* _col2);

    /**
      * @brief       要素1 がCapsuleColliderの場合のコリジョンチェック
      * @param[in]   HWCapsuleCollider*  あたり判定の重なりを見るカプセル型Collider情報1
      * @param[in]   HWCollider*         あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Capsule(HWCapsuleCollider* _col1, HWCollider* _col2);

    /**
      * @brief       分離軸に対する OBB のプロジェクションサイズを計算するためのヘルパー関数
      * @author      Suzuki N
      * @date        24/09/17
      */
    float ProjectOntoAxis(const OBB& obb, const VECTOR& axis)
    {
        // OBB の各軸のスケールと、指定した分離軸とのドット積を使用して投影の大きさを求める
        return obb.halfSize[0] * fabs(VDot(obb.axis[0], axis)) +
            obb.halfSize[1] * fabs(VDot(obb.axis[1], axis)) +
            obb.halfSize[2] * fabs(VDot(obb.axis[2], axis));
    }

    bool CheckOverlapOnAxis(const OBB& obb1, const OBB& obb2, const VECTOR& axis) {
        // 軸がゼロベクトルなら無視する
        if (VSize(axis) < 1e-6) return true;

        // 両方の OBB をその軸に投影
        float projection1 = ProjectOntoAxis(obb1, axis);
        float projection2 = ProjectOntoAxis(obb2, axis);

        // 2つのOBBの中心間のベクトルをその軸に投影
        float distance = fabs(VDot(VSub(obb2.center, obb1.center), axis));

        // 距離が両方の投影の合計より大きい場合は、分離されている
        return distance <= (projection1 + projection2);
    }

    bool OBBvsOBB(const OBB& obb1, const OBB& obb2) {
        VECTOR axis;

        // obb1 の軸
        for (int i = 0; i < 3; ++i) {
            if (!CheckOverlapOnAxis(obb1, obb2, obb1.axis[i])) return false;
        }

        // obb2 の軸
        for (int i = 0; i < 3; ++i) {
            if (!CheckOverlapOnAxis(obb1, obb2, obb2.axis[i])) return false;
        }

        // 両 OBB の軸間の外積で定義される軸
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                axis = VCross(obb1.axis[i], obb2.axis[j]);
                if (!CheckOverlapOnAxis(obb1, obb2, axis)) return false;
            }
        }

        // 全ての軸で分離が見つからなければ、衝突している
        return true;
    }
};

