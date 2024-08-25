#pragma once
#include "Utilities.h"
#include "HandlerWaltan.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		ColliderWaltanの定義ファイル
*/


/**
 * @class		ColliderWaltan
 * @brief       毎Fコライダーコンポーネントのあたり判定を監視し、条件に応じたハンドラーを呼び出す
 */
class CollisionWaltan
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HandlerWaltan;


private:

    /*     メンバ変数     */


    /*     メソッド     */

private:

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


public:

    /**
     * @brief       インスタンスを取得する静的メソッド
     * @detail      初めの一回だけインスタンスを生成する
     * @author      Suzuki N
     * @date        24/08/22
     */
    static CollisionWaltan& Instance();


    //インスタンスのコピー禁止
    //デフォルトのコピーコンストラクタを削除
    CollisionWaltan(const CollisionWaltan&) = delete;
    //デフォルトのコピー代入演算子も削除
    CollisionWaltan& operator=(const CollisionWaltan&) = delete;


    /**
     * @brief       イニシャライズ用のメソッド
     * @detail      インスタンスを生成したときに呼ぶ
     * @return      int 初期化成功の成否
     * @author      Suzuki N
     * @date        24/08/22
     */
    static int Init();
};

