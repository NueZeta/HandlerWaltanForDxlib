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
      * @brief       Boxコライダーがめり込まないようにする処理
      * @author      Suzuki N
      * @date        24/09/17
      */

};

