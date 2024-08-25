#pragma once
#include "HWTransform.h"
#include "HWCollider.h"
#include "HWGameObject.h"
#include "CollisionWaltan.h"


/**
* @author   Suzuki N
* @date     24/07/18
* @note		原則、ハンドラーはすべてHandlerWaltanで呼び出す
*/


/**
 * @class		HandlerWaltan
 * @brief       すべてのハンドラーを管理、実行するクラス
 */
class HandlerWaltan
{

private:

    /*     メンバ変数     */

public:

    /**
     * @brief		デバッグモードで実行するか
     * @History		24/08/23 作成(Suzuki N)
     */
    static bool debugMode;


    /*     メソッド     */

private:

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
    static int Init();

    /**
     * @brief       終了時用のメソッド
     * @author      Suzuki N
     * @date        24/07/29
     */
    static void End();
};
