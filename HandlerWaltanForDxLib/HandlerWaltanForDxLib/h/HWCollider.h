#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"


/**
* @author   Suzuki N
* @date     24/07/18
* @note		あたり判定の情報を保持するコンポーネントの定義
*/


/**
 * @enum	ColliderType
 * @brief	コライダーの種類
 */
enum class ColliderType
{
	//! 立方体(0)
	Box,
	//! 球体(1)
	Sphere,
	//! カプセル型(2)
	Capsule,
};


/**
 * @class	HWCollider
 * @brief	あたり判定の情報を保持するコライダーの基底コンポーネント
 */
class HWCollider : public HWComponent
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     メンバ変数     */

	/**
	 * @brief		コライダーを描画するか
	 * @History		24/09/15 作成(Suzuki N)
	 */
	bool isVisualization;

	/**
	 * @brief		コライダーがトリガーか
	 * @History		24/09/15 作成(Suzuki N)
	 */
	bool isTrigger;

	/**
	 * @brief		コライダーの中心(gameObjectのpositionとの相対距離)
	 * @History		24/09/15 作成(Suzuki N)
	 */
	VECTOR center;

	/**
	 * @brief		コライダーの中心(ワールドの原点との絶対距離)
	 * @History		24/09/15 作成(Suzuki N)
	 */
	VECTOR worldPosition;

protected:

	/**
	 * @brief		コライダーの中心(ローカル)
	 * @History		24/09/15 作成(Suzuki N)
	 */
	VECTOR localCenter;


	/**
	 * @brief		コライダーの種類
	 * @History		24/09/15 作成(Suzuki N)
	 */
	ColliderType colliderType;

	/**
	 * @brief		衝突中のコライダー
	 * @History		24/09/15 作成(Suzuki N)
	 */
	std::vector<HWCollider*> CollidersInCollision;


	/*     メソッド     */

public:

	/**
	 * @brief		コライダータイプを取得する
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	const ColliderType GetColliderType() { return colliderType; }

	/**
	 * @brief		衝突中のコライダー情報を全て取得する
	 * @author		Suzuki N
	 * @date		24/09/18
	 */
	const std::vector<HWCollider*> GetCollidersInCollision() { return CollidersInCollision; }

	/**
	 * @brief		HWColliderのデストラクタ
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	virtual ~HWCollider() {}

protected:

	/**
	 * @brief		HWColliderのコンストラクタ
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	HWCollider();

	/**
	 * @brief		コライダーを描画する
	 * @detail		仮想関数
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	virtual void DrawCollider(){}

	/**
	 * @brief		コライダーの座標をセットする
	 * @detail		仮想関数
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	virtual void SetCollider() {}

#pragma region オーバーライドメソッド

#pragma endregion
};
