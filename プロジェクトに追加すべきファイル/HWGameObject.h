#pragma once
#include <stdarg.h>
#include <algorithm>
#include <unordered_set>
#include "HWComponent.h"
#include "HWTransform.h"
#include "HWRenderer.h"


/**
* @author   Suzuki N
* @date     24/07/16
* @note		コンポーネントを管理する、すべてのオブジェクトが持つクラスの定義
*/


/**
 * @class	CopyType
 * @brief	コピーコンストラクタのタイプ
 */
enum class CopyType
{
	//! シャローコピー(0)
	Shallow,
	//! ディープコピー(1)
	Deep,
};


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


	// 削除待ちオブジェクトの構造体
	struct PendingDestroy {
		HWGameObject* object;
		int time;  // 削除までの残り時間（ms単位）
	};

	/**
	 * @brief   削除予定のオブジェクトを保管するコンテナ
	 * @History 24/11/07 作成(Suzuki N)
	 */
	static std::vector<PendingDestroy> destroyList;

	/**
	 * @brief		アタッチされている全てのコンポーネント
	 * @History		24/06/17 作成(Suzuki N)
	 */
	std::vector<std::unique_ptr<HWComponent>> hwComponents;

	/**
	 * @brief		子オブジェクト
	 * @History		24/09/26 作成(Suzuki N)
	 */
	std::vector<HWGameObject*> children;

	/**
	 * @brief		親オブジェクト
	 * @History		24/09/26 作成(Suzuki N)
	 */
	HWGameObject* parent;

public:

	/**
	 * @brief		アクティブ
	 * @History		24/10/03 作成(Suzuki N)
	 */
	bool active;

	/**
	 * @brief		オブジェクトの名前
	 * @History		24/07/29 作成(Suzuki N)
	 */
	std::string name;

	/**
	 * @brief		オブジェクトのタグ(enumなどで別個定義してください)
	 * @History		24/10/04 作成(Suzuki N)
	 */
	int tag;

	/**
	 * @brief		ハンドラーやUpdateメソッドの優先順位(降順)
	 * @History		24/07/21 作成(Suzuki N)
	 */
	int priority;

	/**
	 * @brief		座標が親オブジェクトの影響を受けるか
	 * @History		24/11/01 作成(Suzuki N)
	 */
	bool isAffect;



	/**
	 * @brief		Transformコンポーネント
	 * @History		24/09/26 作成(Suzuki N)
	 */
	HWTransform* transform;


private:

	/*     メソッド     */

	/**
	 * @brief       プライオリティを参照してソートする(降順)
	 * @author      Suzuki N
	 * @date        24/07/19
	 */
	void BubbleSort();

	/**
	 * @brief       オブジェクトをコピーする(オブジェクトとメモリ上のデータのコピー)
	 * @param[in]	HWGameObject& コピー元になるオブジェクト
	 * @author      Suzuki N
	 * @date        24/10/03
	 */
	void DeepCopy(const HWGameObject& _other);

	/**
	 * @brief       オブジェクトをコピーする(参照のコピー)
	 * @param[in]	HWGameObject& コピー元になるオブジェクト
	 * @author      Suzuki N
	 * @date        24/10/03
	 */
	void ShallowCopy(const HWGameObject& _other);

	/**
	 * @brief       TransformコンポーネントのUpdateメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallTransformUpdate();

	/**
	 * @brief       全てのコンポーネントのUpdateメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllUpdates();

	/**
	 * @brief       全てのコンポーネントのLateUpdateメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllLateUpdates();

	/**
	 * @brief       全てのコンポーネントのOnCollisionEnterCallBackメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionEnters(HWCollider& _collider);

	/**
	 * @brief       全てのコンポーネントのOnCollisionStayCallBackメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionStays(HWCollider& _collider);

	/**
	 * @brief       全てのコンポーネントのOnCollisionExitCallBackメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionExits(HWCollider& _collider);
	
	/**
	 * @brief       全てのコンポーネントのOnTriggerEnterCallBackメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnTriggerEnters(HWCollider& _collider);

	/**
	 * @brief       全てのコンポーネントのOnTriggerStayCallBackメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnTriggerStays(HWCollider& _collider);

	/**
	 * @brief       全てのコンポーネントのOnTriggerExitCallBackメソッドを呼びだす
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnTriggerExits(HWCollider& _collider);


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
	HWGameObject(const std::string& _name);

	/**
	 * @brief		コンストラクタ(プライオリティの初期化宣言)
	 * @param[in]	int プライオリティ
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(const int _priority);

	/**
	 * @brief		コンストラクタ(名前とプライオリティの初期化宣言)
	 * @param[in]	std::string オブジェクト名
	 * @param[in]	int	プライオリティ
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(const std::string& _name, const int _priority);

	/**
	 * @brief		コピーコンストラクタ
	 * @param[in]	HWGameObject& コピー元のHWGameObject
	 * @param[in]	const CopyType コピーの種類
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(const HWGameObject& _other, const CopyType copyType = CopyType::Deep);

#pragma endregion


	/**
	 * @brief		デストラクタ
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	~HWGameObject();


#pragma region Getterメソッド群

	/**
	 * @brief		コンポーネントを追加する
	 * @return		std::vector<HWGameObject*> World上の全てのGameObjectを取得する
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	static std::vector<HWGameObject*> GetGameObjects(){ return gameObjects; }

	/**
	 * @brief		全ての子オブジェクトを取得する
	 * @detail		引数で特定のインデックスの子オブジェクトを取得できる
	 * @return		const std::vector<HWGameObject*>& 全ての子オブジェクトを取得する
	 * @author		Suzuki N
	 * @date		24/10/02
	 */
	std::vector<HWGameObject*>& GetChildren() { return children; }

	/**
	 * @brief		子オブジェクトを取得する
	 * @detail		引数で特定のインデックスの子オブジェクトを取得できる
	 * @return		const std::vector<HWGameObject*>& 全ての子オブジェクトを取得する
	 * @author		Suzuki N
	 * @date		24/10/02
	 */
	HWGameObject* GetChild(const int _index);

	/**
	 * @brief		親オブジェクトを取得する
	 * @return		HWGameObject* 親オブジェクト 
	 * @author		Suzuki N
	 * @date		24/10/02
	 */
	HWGameObject* Parent() { return parent; }


#pragma endregion

#pragma region Setterメソッド群

	/**
	 * @brief		親オブジェクトを設定する
	 * @param[in]	const int 取得する子オブジェクトのインデックス
	 * @param[in]	const bool 座標が親の影響を受けるか
	 * @return		const std::vector<HWGameObject*>& 全ての子オブジェクトを取得する
	 * @author		Suzuki N
	 * @date		24/10/02
	 */
	void SetParent(HWGameObject* _parent, const bool _isAffect = true);

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

		T* ret = dynamic_cast<T*>(hwComponents.back().get());
		// コンポーネントがアタッチされた瞬間に走るメソッドを呼び出す
		ret->Awake();

		// コンポーネントをプライオリティ順に並び変える(降順)
		std::sort(hwComponents.begin(), hwComponents.end(), 
			[](const std::unique_ptr<HWComponent>& a, const std::unique_ptr<HWComponent>& b) {
			return a->priority > b->priority; });

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

	/**
	 * @brief		指定のコンポーネントを返す
	 * @param[in]	HWGameObject* 削除するオブジェクト
	 * @param[in]	int			  何秒後に削除するか 
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	static void Destroy(HWGameObject* _obj, float delay = 0.0f);

};