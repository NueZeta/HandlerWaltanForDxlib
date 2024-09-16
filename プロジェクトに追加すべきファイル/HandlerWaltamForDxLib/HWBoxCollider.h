#pragma once
#include "HWCollider.h"
//#include "HandlerWaltan.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		立方型のコライダーコンポーネントの定義
*/


/**
 * @class	HWBoxCollider
 * @brief	立方型のコライダーコンポーネント
 */
class HWBoxCollider : public HWCollider
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     メンバ変数     */

	/**
	 * @brief		コライダーのサイズ
	 * @History		24/09/16 作成(Suzuki N)
	 */
	VECTOR size;


	/*     メソッド     */

public:

	/**
	 * @brief		コンストラクタ
	 * @detail		引数でコライダーのサイズを指定可
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	HWBoxCollider();

	/**
	 * @brief		コンストラクタ
	 * @detail		引数でコライダーのサイズを指定可
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	HWBoxCollider(VECTOR _size);

	/**
	 * @brief		コンストラクタ
	 * @detail		引数でコライダーのサイズを指定可
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	HWBoxCollider(float _sizeX, float _sizeY, float _sizeZ);

protected:

#pragma region オーバーライドメソッド

	/**
	 * @brief		立方体のコライダーを描画する
	 * @detail		オーバライドメソッド
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	void DrawCollider() override;

	/**
	 * @brief		HWGameObjectにアタッチされた瞬間に働く
	 * @detail		オーバライドメソッド
	 * @author		Suzuki N
	 * @date		24/09/15
	 */
	void Awake()override;

	/**
	 * @brief		毎フレーム呼ばれる
	 * @detail		オーバーライドメソッド
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	void Update() override;

#pragma endregion
};

