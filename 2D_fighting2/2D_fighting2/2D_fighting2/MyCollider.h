#pragma once
#include <iostream>
#include "MyComponent.h"


/**
* @author   Suzuki N
* @date     24/07/18
* @note		あたり判定の情報を保持するコンポーネントの定義
*/


/**
 * @enum		eColliderType
 * @brief		コライダータイプ
 */
enum class eColliderType
{
	//!通常の四角形型のあたり判定(0)
	BoxCollider,
};


/**
 * @class		myTransform
 * @brief		オブジェクトの座標や回転などを保持するコンポーネント
 */
class MyCollider : public MyComponent
{
private:


public:
	/*     メンバ変数     */

	/**
	 * @brief		コライダータイプ
	 * @History		24/07/18 作成(Suzuki N)
	 */
	eColliderType colliderType;
	


	/*     メソッド     */


	/**
	 * @brief		MyColliderのコンストラクタ
	 * @detail		イニシャライズ用
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	MyCollider() : colliderType(eColliderType::BoxCollider)
	{
	}


#pragma region オーバーライドメソッド

	/**
	 * @brief		毎フレーム呼ばれる
	 * @detail		オーバーライド関数
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void Start() override
	{
		OnCollisionEnterHandler();
	}


	void OnCollisionEnter() override
	{
		cout << "MyColliderコンポーネントのOnCollisionEnterメソッド\n";
	}

#pragma endregion
};
