#include<iostream>
#include<memory>
#include<vector>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;


/**
 * @author		Suzuki N
 * @date		24/06/17
 * @note		コンポーネント志向のサンプルファイル
 * @History		ファイルに履歴などを明記する場合はここへ書き込む
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


//myComponentクラスがメンバ変数にGameObjectクラスを持たせるために前方宣言
class MyGameObject;


/**
 * @class		myComponent
 * @brief		全てのコンポーネントクラスの基底クラス
 */
class MyComponent
{
public:
	/*     メンバ変数     */

	/**
	 * @brief		このコンポーネントがアタッチされているmyGameObject
	 * @History		24/06/17 作成(Suzuki N)
	 */
	MyGameObject* gameObject;

	/*     メソッド     */

	/**
	 * @brief		アタッチされているmyGameObjectにインスタンスを代入する
	 * @param[in]	myGameObject* _gameObject  代入するmyGameObject
	 * @date		24/06/17
	 */
	void SetMyGameObject(MyGameObject* _gameObject)
	{
		gameObject = _gameObject;
	}

	/**
	 * @brief		アタッチされているmyGameObjectを返す
	 * @return		コンポーネントがアタッチされているmyGameObject
	 * @date		24/06/17
	 */
	MyGameObject* GetMyGameObject()
	{
		return gameObject;
	}


	/**
	 * @brief		myGameObjectにアタッチされた瞬間に働く
	 * @ditail		仮想関数
	 * @date		24/06/17
	 */
	virtual void Start() {}


	/**
	 * @brief		毎フレーム呼ばれるメソッド
	 * @ditail		仮想関数
	 * @date		24/06/17
	 */
	virtual void Update() {}
};



/**
 * @class		myTransform
 * @brief		オブジェクトの座標や回転などを保持するクラス
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



/**
 * @class		
 * @brief		クラス
 */
class MyCollider : public MyComponent
{

};



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
	/*     メソッド     */


	/**
	 * @brief		コンポーネントを追加する
	 * @param[in]	アタッチするコンポーネント
	 * @author		Suzuki N
	 * @date		24/06/17
	 */	
	void AddComponent(unique_ptr<MyComponent> _component)
	{
		_component->SetMyGameObject(this);
		_component->Start();
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
		static_assert(is_base_of<MyComponent, T>::value, "T must derive from Component");

		//javaやC#でいうところのforeach構文
		for (auto& component : myComponents)
		{
			if (auto* targetComponent = dynamic_cast<T*>(component.get()))
				return targetComponent;
		}

		return nullptr;
	}

	/**
	 * @brief		アタッチされているコンポーネントのUpdateメソッドを全て呼び出す
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void MyComponentsUpdate()
	{
		for (unique_ptr<MyComponent>& component : myComponents)
			component->Update();
	}
};



int main()
{
	unique_ptr<MyGameObject> obj = make_unique<MyGameObject>();

	obj->AddComponent(make_unique<MyTransform>());

	MyTransform* transform = obj->GetMyComponent<MyTransform>();

	cout << "X = " << transform->GetPosition().x << endl;
	cout << "Y = " << transform->GetPosition().y << endl;
	cout << "Z = " << transform->GetPosition().z << endl;

	transform->Position = { -1, -2, -3 };


	cout << "\n\n";

	MyGameObject* obj2 = transform->GetMyGameObject();

	auto gege = obj2->GetMyComponent<MyTransform>();

	cout << "X = " << gege->GetPosition().x << endl;
	cout << "Y = " << gege->GetPosition().y << endl;
	cout << "Z = " << gege->GetPosition().z << endl;

	
	obj->MyComponentsUpdate();


	return 0;
}