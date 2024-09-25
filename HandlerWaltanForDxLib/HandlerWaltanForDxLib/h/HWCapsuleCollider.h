#pragma once
#include "HWCollider.h"
#include "HandlerWaltan.h"
#include "CollisionWaltan.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		カプセル型のコライダーコンポーネントの定義
*/


/**
 * @class	HWCapsuleCollider
 * @brief	カプセル型のコライダーコンポーネント
 */
class HWCapsuleCollider : public HWCollider
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     メンバ変数     */

	/**
	 * @brief		コライダーの始点
	 * @History		24/09/16 作成(Suzuki N)
	 */
	VECTOR startPos;

	/**
	 * @brief		コライダーの終点
	 * @History		24/09/16 作成(Suzuki N)
	 */
	VECTOR endPos;

	/**
	 * @brief		コライダーの半径
	 * @History		24/09/16 作成(Suzuki N)
	 */
	float radius;

	/**
	 * @brief		回転行列
	 * @History		24/09/16 作成(Suzuki N)
	 */
	MATRIX mRotate;


	 /*     メソッド     */

public:

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	HWCapsuleCollider();

	/**
	 * @brief		デストラクタ
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	~HWCapsuleCollider();

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

#pragma endregion
};

