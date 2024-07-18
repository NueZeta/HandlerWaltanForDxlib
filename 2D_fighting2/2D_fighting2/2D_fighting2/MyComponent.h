#pragma once

using namespace std;


/**
* @author   Suzuki N
* @date     24/07/16
* @note     すべてのコンポーネントの基底クラスの定義ファイル
*/


//myComponentクラスがメンバ変数にMyGameObjectクラスを持たせるために前方宣言
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