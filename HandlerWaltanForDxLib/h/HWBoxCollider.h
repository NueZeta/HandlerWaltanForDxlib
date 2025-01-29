#pragma once
#include "HWCollider.h"
#include "HandlerWaltan.h"
#include "CollisionWaltan.h"


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

	/**
	 * @brief		回転行列
	 * @History		24/09/16 作成(Suzuki N)
	 */
	MATRIX mRotate;

	/**
	 * @brief		コライダーの各頂点座標
	 * @History		24/09/18 作成(Suzuki N)
	 */
	VECTOR vertex[2][4];

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
	HWBoxCollider(const VECTOR& _size);

	/**
	 * @brief		コンストラクタ
	 * @detail		引数でコライダーのサイズを指定可
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	HWBoxCollider(const float& _sizeX, const float& _sizeY, const float& _sizeZ);

	/**
	 * @brief		デストラクタ
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	~HWBoxCollider();

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
	 * @brief		立方体のコライダーを構成する
	 * @detail		オーバライドメソッド
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	void SetCollider() override;

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

	/**
	 * @brief		コライダー衝突時に働くメソッド
	 * @detail		オーバーライドメソッド
	 * @author		Suzuki N
	 * @date		24/09/26
	 */
	void OnCollisionEnter(HWCollider& _collider)override;

#pragma endregion
};

