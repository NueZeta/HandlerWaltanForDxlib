#pragma once


/**
* @author   Suzuki N
* @date     24/07/20
* @note		汎用的なクラスの定義をまとめたヘッダーファイル
*/


/**
 * @class		Property
 * @brief       メソッドを通して値の取得や変更を行う為のラッパークラス
 */
template<typename T>
class Property
{

private:

    /*     メンバ変数     */

    /**
     * @brief   ラッピングする変数
     * @History 24/07/20 作成(Suzuki N)
     */
    T data;


    /*     メソッド     */

public:

    /**
     * @brief       コンストラクタ
     * @param[in]   T _initial 初期値
     * @author		Suzuki N
     * @date		24/07/21
     */
    Property(T _initial) : data(_initial) {}


    /**
     * @brief       新たに値をセットする
     * @param[in]   T _data 変更後の値
     * @author		Suzuki N
     * @date		24/07/21
     */
    void Set(T _data)
    {
        data = _data;
    }


    /**
     * @brief       値を返す
     * @return      T data
     * @author		Suzuki N
     * @date		24/07/21
     */
    T Get() { return data; }
};