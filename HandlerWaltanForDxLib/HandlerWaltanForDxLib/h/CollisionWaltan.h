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
        VECTOR c;      
        //! OBBの各軸(正規化された)
        VECTOR u[3];     
        //! 各軸方向のハーフサイズ
        VECTOR e;
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

    void ColliderHitCallBacks(HWCollider* _col1, HWCollider* _col2, bool _isTrigger);

    /**
      * @brief       OBB同士の当たり判定
      * @author      Suzuki N
      * @date        24/09/24
      */
    int TestOBBOBB(OBB* a, OBB* b)
    {
        const float EPSILON = 1.175494e-37;

        float R[3][3], AbsR[3][3];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                R[i][j] = VDot(a->u[i], b->u[j]);
                AbsR[i][j] = fabsf(R[i][j]) + EPSILON;
            }
        }

        VECTOR t = VSub(b->c, a->c);
        t = VGet(VDot(t, a->u[0]), VDot(t, a->u[1]), VDot(t, a->u[2]));

        //軸L=A0, L=A1, L=A2判定
        float ra, rb;

            ra = a->e.x;
            rb = b->e.x * AbsR[0][0] + b->e.y * AbsR[0][1] + b->e.z * AbsR[0][2];
            if (fabsf(t.x) > ra + rb)return 0;

            ra = a->e.y;
            rb = b->e.x * AbsR[1][0] + b->e.y * AbsR[1][1] + b->e.z * AbsR[1][2];
            if (fabsf(t.y) > ra + rb)return 0;
            
            ra = a->e.z;
            rb = b->e.x * AbsR[2][0] + b->e.y * AbsR[2][1] + b->e.z * AbsR[2][2];
            if (fabsf(t.z) > ra + rb)return 0;

        //軸L=B0, L=B1, L=B2判定
            ra = a->e.x * AbsR[0][0] + a->e.y * AbsR[1][0] + a->e.z * AbsR[2][0];
            rb = b->e.x;
            if (fabsf(t.x * R[0][0] + t.y * R[1][0] + t.z * R[2][0]) > ra + rb)return 0;

            ra = a->e.x * AbsR[0][1] + a->e.y * AbsR[1][1] + a->e.z * AbsR[2][1];
            rb = b->e.y;
            if (fabsf(t.x * R[0][1] + t.y * R[1][1] + t.z * R[2][1]) > ra + rb)return 0;
            
            ra = a->e.x * AbsR[0][2] + a->e.y * AbsR[1][2] + a->e.z * AbsR[2][2];
            rb = b->e.y;
            if (fabsf(t.x * R[0][2] + t.y * R[1][2] + t.z * R[2][2]) > ra + rb)return 0;
        



        //軸L=A0 X B0判定
        ra = a->e.y * AbsR[2][0] + a->e.z * AbsR[1][0];
        rb = b->e.y * AbsR[0][2] + b->e.z * AbsR[0][1];
        if (fabsf(t.z * R[1][0] - t.y * R[2][0]) > ra + rb)return 0;

        //軸L=A0 X B1判定
        ra = a->e.y * AbsR[2][1] + a->e.z * AbsR[1][1];
        rb = b->e.x * AbsR[0][2] + b->e.z * AbsR[0][0];
        if (fabsf(t.z * R[1][1] - t.y * R[2][1]) > ra + rb)return 0;

        //軸L=A0 X B2判定
        ra = a->e.y * AbsR[2][2] + a->e.z * AbsR[1][2];
        rb = b->e.x * AbsR[0][1] + b->e.y * AbsR[0][0];
        if (fabsf(t.z * R[1][2] - t.y * R[2][2]) > ra + rb)return 0;

        //軸L=A1 X B0判定
        ra = a->e.x * AbsR[2][0] + a->e.z * AbsR[0][0];
        rb = b->e.y * AbsR[1][2] + b->e.z * AbsR[1][1];
        if (fabsf(t.x * R[2][0] - t.z * R[0][0]) > ra + rb)return 0;

        //軸L=A1 X B1判定
        ra = a->e.z * AbsR[2][1] + a->e.z * AbsR[0][1];
        rb = b->e.z * AbsR[1][2] + b->e.z * AbsR[1][0];
        if (fabsf(t.x * R[2][1] - t.z * R[0][1]) > ra + rb)return 0;

        //軸L=A1 X B2判定
        ra = a->e.x * AbsR[2][2] + a->e.z * AbsR[0][2];
        rb = b->e.x * AbsR[1][1] + b->e.y * AbsR[1][0];
        if (fabsf(t.x * R[2][2] - t.z * R[0][2]) > ra + rb)return 0;

        //軸L=A2 X B0判定
        ra = a->e.x * AbsR[1][0] + a->e.y * AbsR[0][0];
        rb = b->e.y * AbsR[2][2] + b->e.z * AbsR[2][1];
        if (fabsf(t.y * R[0][0] - t.x * R[1][0]) > ra + rb)return 0;

        //軸L=A2 X B1判定
        ra = a->e.x * AbsR[1][1] + a->e.y * AbsR[0][1];
        rb = b->e.x * AbsR[2][2] + b->e.z * AbsR[2][0];
        if (fabsf(t.y * R[0][1] - t.y * R[1][1]) > ra + rb)return 0;

        //軸L=A2 X B2判定
        ra = a->e.x * AbsR[1][2] + a->e.y * AbsR[0][2];
        rb = b->e.x * AbsR[2][1] + b->e.y * AbsR[2][0];
        if (fabsf(t.y * R[0][2] - t.x * R[1][2]) > ra + rb)return 0;

        return 1;
    }
};

