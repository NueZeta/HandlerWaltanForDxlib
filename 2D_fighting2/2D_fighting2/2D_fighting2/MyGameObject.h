#pragma once
#include <vector>
#include <memory>
#include "MyComponent.h"


/**
* @author   Suzuki N
* @date     24/07/16
* @note		コンポーネントを管理する、すべてのオブジェクトが持つクラスの定義
*/


/**
 * @class		MyGameObject
 * @brief       オブジェクトに関する情報をまとめたクラス
 */
class MyGameObject
{
private:
	/*     メンバ変数     */

	/**
	 * @brief		アタッチされている全てのコンポーネント
	 * @History		24/06/17 作成(Suzuki N)
	 */
	vector<unique_ptr<MyComponent>> myComponents;


public:
	/**
	 * @brief		ハンドラーやUpdateメソッドの優先順位
	 * @History		24/07/21 作成(Suzuki N)
	 */
	int priority;


public:
	/*     メソッド     */


	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	MyGameObject() : priority(0)
	{
	}


	/**
	 * @brief		コンポーネントを追加する
	 * @param[in]	アタッチするコンポーネント
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void AddMyComponent(unique_ptr<MyComponent> _component)
	{
		_component->SetMyGameObject(this);
		//_component->Start();
		myComponents.push_back(move(_component));
	}

	/**
	 * @brief		指定のコンポーネントを返す
	 * @return		アタッチされていた場合はインスタンスを返し、それ以外ならnullPtrを返す
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	template<typename T>
	T* GetMyComponent()
	{
		//テンプレートのTypeがComponentの派生クラスか調べ、違った場合はコンパイル時にエラーを吐く
		static_assert(is_base_of<MyComponent, T>::value, "コンポーネント以外はアタッチできません");

		//javaやC#でいうところのforeach構文
		for (auto& component : myComponents)
		{
			if (auto* targetComponent = dynamic_cast<T*>(component.get()))
				return targetComponent;
		}

		return nullptr;
	}
};