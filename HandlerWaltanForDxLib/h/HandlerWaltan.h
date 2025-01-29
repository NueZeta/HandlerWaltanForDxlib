#pragma once
#include "CollisionWaltan.h"
#include "HWAnimator.h"
#include "HWBoxCollider.h"
#include "HWCamera.h"
#include "HWEffect.h"
#include "HWCapsuleCollider.h"
#include "HWSphereCollider.h"
#include "HWGameObject.h"
#include "HWRenderer.h"
#include "HWTransform.h"
#include "InputSystem.h"


/**
* @author   Suzuki N
* @date     24/07/18
* @note		原則、ハンドラーはすべてHandlerWaltanで呼び出す
*/


/**
 * @class	HandlerWaltan
 * @brief   すべてのハンドラーを管理、実行するクラス
 */
class HandlerWaltan
{
public:

    /*     メンバ変数     */

    /**
     * @brief		デバッグモードで実行するか
     * @History		24/08/23 作成(Suzuki N)
     */
    static bool debugMode;

private:


private:

    /*     メソッド     */

    /**
     * @brief       コンストラクタ
     * @author      Suzuki N
     * @date        24/07/19
     */
    HandlerWaltan();

    /**
     * @brief       デストラクタ
     * @author      Suzuki N
     * @date        24/07/19
     */
    ~HandlerWaltan();


public:

    /**
      * @brief       全てのUpdateメソッドを全て呼び出す
      * @author      Suzuki N
      * @date        24/08/22
      */
    void Update();

    /**
     * @brief       インスタンスを取得する静的メソッド
     * @detail      初めの一回だけインスタンスを生成する
     * @author      Suzuki N
     * @date        24/07/19
     */
    static HandlerWaltan& Instance();


    //インスタンスのコピー禁止
    //デフォルトのコピーコンストラクタを削除
    HandlerWaltan(const HandlerWaltan&) = delete;
    //デフォルトのコピー代入演算子も削除
    HandlerWaltan& operator=(const HandlerWaltan&) = delete;


    /**
     * @brief       イニシャライズ用のメソッド
     * @detail      インスタンスを生成したときに呼ぶ
     * @return      int 初期化成功の成否
     * @author      Suzuki N
     * @date        24/07/29
     */
    static int Init(int _particle = 8000);

    /**
     * @brief       終了時用のメソッド
     * @author      Suzuki N
     * @date        24/07/29
     */
    static void End();
};
