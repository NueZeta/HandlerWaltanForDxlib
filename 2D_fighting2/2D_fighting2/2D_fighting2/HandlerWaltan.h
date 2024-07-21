#pragma once
#include "MyTransform.h"
#include "MyCollider.h"
#include "MyGameObject.h"


/**
* @author   Suzuki N
* @date     24/07/18
* @note		原則、ComponentのハンドラーはすべてHandlerWaltanで呼び出す
*/


/**
 * @class		HandlerWaltan
 * @brief       すべてのハンドラーメソッドの呼び出しを管理するクラス
 * @detail		シングルトンで設計する
 */
class HandlerWaltan
{

    /*     メンバ変数     */

private:

    /**
     * @brief   インスタンス化されたオブジェクト全てを保管しておくコンテナ
     * @History 24/07/19 作成(Suzuki N)
     */
    vector<MyGameObject*> gameObjects;



 /*     メソッド     */

private:

    /**
     * @brief       コンストラクタ
     * @detail      外部からインスタンスを生成出来ないようにするためのプライベート
     * @author      Suzuki N
     * @date        24/07/19
     */
    HandlerWaltan() {}


public:

    /**
     * @brief       インスタンスを取得する静的メソッド
     * @detail      初めの一回だけインスタンスを生成する
     * @author      Suzuki N
     * @date        24/07/19
     */
    static HandlerWaltan& Instance()
    {
        //!シングルトンインスタンス
        static HandlerWaltan instance;
        return instance;
    }

    //インスタンスのコピー禁止
    //デフォルトのコピーコンストラクタを削除
    HandlerWaltan(const HandlerWaltan&) = delete;
    //デフォルトのコピー代入演算子も削除
    HandlerWaltan& operator=(const HandlerWaltan&) = delete;


    /**
     * @brief       インスタンス化されたMyGameObjectを保管しておく
     * @detail      MyGameObjectのコンストラクタでのみ呼ばれる
     * @param[in]   MyGameObject　追加するMyGameObject
     * @author      Suzuki N
     * @date        24/07/19
     */
    void AddMyGameObject(MyGameObject* _gameObject)
    {
        gameObjects.push_back(_gameObject);

        cout << gameObjects[0]->priority << "\n";

        _gameObject->priority = -20;

        cout << gameObjects[0]->priority << "\n";
    }
};

