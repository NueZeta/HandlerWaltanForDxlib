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
        //! OBBの各軸(正規化された)
        VECTOR axis[3];     
        //! 各軸方向のハーフサイズ
        VECTOR extent;
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
      * @brief       OBB同士のあたり判定
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CheckOBBIntersection(const OBB& _obb1, const OBB& _obb2)
    {
        // 各OBBの軸
        const VECTOR& a0 = _obb1.axis[0];
        const VECTOR& a1 = _obb1.axis[1];
        const VECTOR& a2 = _obb1.axis[2];

        const VECTOR& b0 = _obb2.axis[0];
        const VECTOR& b1 = _obb2.axis[1];
        const VECTOR& b2 = _obb2.axis[2];

        //! obb1 と obb2 間の距離ベクトル
        VECTOR dir = VSub(_obb2.center, _obb1.center);

        // 各軸で投影して分離軸をチェックするためのサポート変数
        float c[3][3];
        float AbsC[3][3];
        float rA, rB;

        // 各軸に対する投影を計算
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                c[i][j] = VDot(_obb1.axis[i], _obb2.axis[j]);
                AbsC[i][j] = fabs(c[i][j]) + FLT_EPSILON;  // 浮動小数点エラー対策
            }

        // obb1 の軸を基準にして分離軸をテスト
        rA = _obb1.extent.x;
        rB = _obb2.extent.x * AbsC[0][1] + _obb2.extent.y * 
            AbsC[0][1] + _obb2.extent.z * AbsC[0][2];
        // obb1 と obb2 間の距離が rA + rB (２つのOBBの半分の投影距離)
        // よりも大きかったらこの軸では接触していない
        if (fabs(VDot(a0, dir)) > rA + rB)
            return false;

        rA = _obb1.extent.y;
        rB = _obb2.extent.x * AbsC[1][0] + _obb2.extent.y * 
            AbsC[1][1] + _obb2.extent.z * AbsC[1][2];
        // obb1 と obb2 間の距離が rA + rB (２つのOBBの半分の投影距離)
        // よりも大きかったらこの軸では接触していない
        if (fabs(VDot(a1, dir)) > rA + rB)
            return false;

        rA = _obb1.extent.z;
        rB = _obb2.extent.x * AbsC[2][0] + _obb2.extent.y * 
            AbsC[2][1] + _obb2.extent.z * AbsC[2][2];
        // obb1 と obb2 間の距離が rA + rB (２つのOBBの半分の投影距離)
        // よりも大きかったらこの軸では接触していない
        if (fabs(VDot(a2, dir)) > rA + rB)
            return false;

        // obb2 の軸を基準にして分離軸をテスト
        rB = _obb1.extent.x * AbsC[0][1] + _obb1.extent.y * 
            AbsC[0][1] + _obb1.extent.z * AbsC[0][2];
        rA = _obb2.extent.x;
        // obb1 と obb2 間の距離が rA + rB (２つのOBBの半分の投影距離)
        // よりも大きかったらこの軸では接触していない
        if (fabs(VDot(a0, dir)) > rA + rB)
            return false;

        rB = _obb1.extent.x * AbsC[1][0] + _obb1.extent.y * 
            AbsC[1][1] + _obb1.extent.z * AbsC[1][2];
        rA = _obb2.extent.y;
        // obb1 と obb2 間の距離が rA + rB (２つのOBBの半分の投影距離)
        // よりも大きかったらこの軸では接触していない
        if (fabs(VDot(a1, dir)) > rA + rB)
            return false;

        rB = _obb1.extent.x * AbsC[2][0] + _obb1.extent.y * 
            AbsC[2][1] + _obb1.extent.z * AbsC[2][2];
        rA = _obb2.extent.z;
        // obb1 と obb2 間の距離が rA + rB (２つのOBBの半分の投影距離)
        // よりも大きかったらこの軸では接触していない
        if (fabs(VDot(a2, dir)) > rA + rB)
            return false;

        // どの軸から見ても接触している
        return true;
    }
};

