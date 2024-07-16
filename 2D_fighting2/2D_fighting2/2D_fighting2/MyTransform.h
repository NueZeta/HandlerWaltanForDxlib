#include<iostream>
#include"MyComponent.h"
#pragma once


/**
* @author   Suzuki N
* @date     24/07/16
* @note		座標系の情報を保持するコンポーネントの定義
*/


/**
*  @struct		myVector3
*  @brief		3Dベクトル
*/
typedef struct
{
	float x;
	float y;
	float z;
}MyVector3;


/**
 * @class		myTransform
 * @brief		オブジェクトの座標や回転などを保持するコンポーネント
 */
class MyTransform : public MyComponent
{
private:


public:
	/*     メンバ変数     */

	/**
	 * @brief		ワールド座標
	 * @History		24/06/17 作成(Suzuki N)
	 */
	MyVector3 Position = { 1,0,0.5 };


	/*     メソッド     */

	/**
	 * @brief		毎フレーム呼ばれる
	 * @ditail		オーバーライド関数
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void Update() override
	{
		cout << "MyTransformコンポーネントのUpdateメソッド\n";
	}

	/**
	 * @brief		ワールド座標を返す
	 * @return		ワールド座標
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	MyVector3 GetPosition() { return Position; }
};
