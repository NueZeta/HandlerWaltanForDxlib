#pragma once
#include <functional>
#include "Utilities.h"


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


private:

	/**
	 * @brief		衝突判定を取った時に呼ばれるコールバック関数
	 * @History		24/07/19 作成(Suzuki N)
	 */
	function<void()> OnCollisionEnterCallBack;

	/**
	 * @brief		衝突判定を取っている間に呼ばれるコールバック関数
	 * @History		24/07/19 作成(Suzuki N)
	 */
	function<void()> OnCollisionStayCallBack;

	/**
	 * @brief		衝突判定が解かれた時に呼ばれるコールバック関数
	 * @History		24/07/19 作成(Suzuki N)
	 */
	function<void()> OnCollisionExitCallBack;


public:


	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	MyComponent()
	{
		//各コールバック関数にオーバーライドされたメソッドを代入する
		OnCollisionEnterCallBack = bind(&MyComponent::OnCollisionEnter, this);
		OnCollisionStayCallBack = bind(&MyComponent::OnCollisionStay, this);
		OnCollisionExitCallBack = bind(&MyComponent::OnCollisionExit, this);
	}


	/**
	 * @brief		アタッチされているmyGameObjectにインスタンスを代入する
	 * @param[in]	myGameObject* _gameObject  代入するmyGameObject
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void SetMyGameObject(MyGameObject* _gameObject)
	{
		gameObject = _gameObject;
	}

	/**
	 * @brief		アタッチされているmyGameObjectを返す
	 * @return		コンポーネントがアタッチされているmyGameObject
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	MyGameObject* GetMyGameObject()
	{
		return gameObject;
	}

protected:

#pragma region 仮想関数群

	/**
	 * @brief		myGameObjectにアタッチされた瞬間に働く
	 * @detail		仮想関数
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	virtual void Start() {}


	/**
	 * @brief		毎フレーム呼ばれるメソッド
	 * @detail		仮想関数
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	virtual void Update() {}


	/**
	 * @brief		コライダー衝突時に働くメソッド
	 * @detail		仮想関数
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionEnter() {}


	/**
	 * @brief		コライダー衝突中に働くメソッド
	 * @detail		仮想関数
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionStay() {}


	/**
	 * @brief		コライダー衝突が解除時に働くメソッド
	 * @detail		仮想関数
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionExit() {}

#pragma endregion

	public:

#pragma region 登録されたコールバック関数を呼ぶメソッド群

	/**
	 * @brief		登録された衝突時に働くメソッドを働かせる
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnCollisionEnterHandler()
	{
		if (OnCollisionEnterCallBack)
			OnCollisionEnterCallBack();
	}

#pragma endregion
};
