#pragma once
#include "DxLib.h"
#include "Utilities.h"


/**
* @author   Suzuki N
* @date     24/06/17
* @note     すべてのコンポーネントの基底クラスの定義ファイル
*/


//HWComponentクラスがメンバ変数にHWGameObjectクラスを持たせるために前方宣言
class HWGameObject;
class HWTransform;


/**
 * @class	HWComponent
 * @brief	全てのコンポーネントの基底クラス
 */
class HWComponent
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     メンバ変数     */

	/**
	 * @brief		このコンポーネントがアタッチされているHWGameObject
	 * @History		24/06/17 作成(Suzuki N)
	 */
	HWGameObject* gameObject;

	/**
	 * @brief		HWGameObjectにアタッチされているHWTransform
	 * @History		24/06/17 作成(Suzuki N)
	 */
	HWTransform* transform;

	/**
	 * @brief		複数アタッチ可能なコンポーネントか
	 * @History		24/08/03 作成(Suzuki N)
	 */
	bool isMultiplePossession;

	/**
	 * @brief		コンポーネントのアクティブ
	 * @History		24/08/03 作成(Suzuki N)
	 */
	bool active;


private:

	/**
	 * @brief		衝突判定を取った時に呼ばれるコールバック関数
	 * @History		24/07/19 作成(Suzuki N)
	 */
	std::function<void()> OnCollisionEnterCallBack;

	/**
	 * @brief		衝突判定を取っている間に呼ばれるコールバック関数
	 * @History		24/07/19 作成(Suzuki N)
	 */
	std::function<void()> OnCollisionStayCallBack;
	
	/**
	 * @brief		衝突判定が解かれた時に呼ばれるコールバック関数
	 * @History		24/07/19 作成(Suzuki N)
	 */
	std::function<void()> OnCollisionExitCallBack;


public:

	/*     メソッド     */

	/**
	 * @brief		デストラクタ
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual ~HWComponent(){}

protected:

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	HWComponent();

#pragma region 仮想関数群

	/**
	 * @brief		HWGameObjectにアタッチされた瞬間に働く
	 * @detail		仮想関数
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	virtual void Awake() {}


	/**
	 * @brief		最初のUpdateメソッドの直前に働く
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

#pragma region 登録されたコールバック関数を呼ぶメソッド群

	/**
	 * @brief		登録された衝突時に働くメソッドを働かせる
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnCollisionEnterHandler();

	/**
	 * @brief		登録された衝突時に働くメソッドを働かせる
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnCollisionStayHandler();

	/**
	 * @brief		登録された衝突時に働くメソッドを働かせる
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnCollisionExsitHandler();

#pragma endregion
};

