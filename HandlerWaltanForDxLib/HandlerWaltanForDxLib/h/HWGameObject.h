#pragma once
#include <stdarg.h>
#include <algorithm>
#include "HWComponent.h"
#include "HWTransform.h"


/**
* @author   Suzuki N
* @date     24/07/16
* @note		コンポーネントを管理する、すべてのオブジェクトが持つクラスの定義
*/


/**
 * @class	HWGameObject
 * @brief	オブジェクトに関する情報をまとめたクラス
 */
class HWGameObject
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HandlerWaltan;
	friend class CollisionWaltan;

private:

	/*     メンバ変数     */

	/**
	 * @brief   インスタンス化されたオブジェクト全てを保管しておくコンテナ
	 * @History 24/07/19 作成(Suzuki N)
	 */
	static std::vector<HWGameObject*> gameObjects;

	/**
	 * @brief		アタッチされている全てのコンポーネント
	 * @History		24/06/17 作成(Suzuki N)
	 */
	std::vector<std::unique_ptr<HWComponent>> hwComponents;

public:

	/**
	 * @brief		オブジェクトの名前
	 * @History		24/07/29 作成(Suzuki N)
	 */
	std::string name;

	/**
	 * @brief		ハンドラーやUpdateメソッドの優先順位(降順)
	 * @History		24/07/21 作成(Suzuki N)
	 */
	int priority;


private:

	/*     メソッド     */

	/**
	 * @brief       プライオリティを参照してソートする
	 * @author      Suzuki N
	 * @date        24/07/19
	 */
	void BubbleSort();

	/**
	 * @brief       全てのコンポーネントのUpdateメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllUpdates();

	/**
	 * @brief       全てのコンポーネントのOnCollisionEnterCallBackメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionEnters(HWCollider* _collider);

	/**
	 * @brief       全てのコンポーネントのOnCollisionStayCallBackメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionStays(HWCollider* _collider);

	/**
	 * @brief       全てのコンポーネントのOnCollisionExitCallBackメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionExits(HWCollider* _collider);


public:

#pragma region コンストラクタ

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject();

	/**
	 * @brief		コンストラクタ(名前の初期化宣言)
	 * @param[in]	std::string オブジェクト名
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(std::string _name);

	/**
	 * @brief		コンストラクタ(プライオリティの初期化宣言)
	 * @param[in]	int プライオリティ
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(int _priority);

	/**
	 * @brief		コンストラクタ(名前とプライオリティの初期化宣言)
	 * @param[in]	std::string オブジェクト名
	 * @param[in]	int	プライオリティ
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(std::string _name, int _priority);

#pragma endregion


	/**
	 * @brief		デストラクタ
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	~HWGameObject();


#pragma region Getterメソッド群

	static std::vector<HWGameObject*> GetGameObjects(){ return gameObjects; }

#pragma endregion

	/**
	 * @brief		コンポーネントを追加する
	 * @param[in]	std::unique_ptr<HWComponent> アタッチするコンポーネント
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	template<class T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		//テンプレートのTypeがComponentの派生クラスか調べ、違った場合はコンパイル時にエラーを吐く
		static_assert(std::is_base_of<HWComponent, T>::value, "Error : Attempted to attach a non-component");


		std::unique_ptr<HWComponent> component = std::make_unique<T>(std::forward<Args>(args)...);

		// コンポーネントからアタッチされているGameObjectとTransformを確認できるようにする
		component->gameObject = this;
		component->transform = (GetComponent<HWTransform>());
		hwComponents.push_back(std::move(component));

		T* ret = dynamic_cast<T*>(hwComponents[hwComponents.size() - 1].get());
		// コンポーネントがアタッチされた瞬間に走るメソッドを呼び出す
		ret->Awake();

		return ret;
	}

	/**
	 * @brief		指定のコンポーネントを返す
	 * @return		アタッチされていた場合はインスタンスを返し、それ以外ならnullPtrを返す
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	template<class T >
	T* GetComponent()
	{
		//テンプレートのTypeがComponentの派生クラスか調べ、違った場合はコンパイル時にエラーを吐く
		static_assert(std::is_base_of<HWComponent, T>::value, "Error : Trying to get something other than Component");

		//javaやC#でいうところのforeach構文
		for (auto& component : hwComponents)
		{
			if (auto* targetComponent = dynamic_cast<T*>(component.get()))
				return targetComponent;
		}

		return nullptr;
	}
};