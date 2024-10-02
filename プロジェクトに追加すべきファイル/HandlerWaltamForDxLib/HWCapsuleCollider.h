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
	 * @brief		コライダーの高さ (自身で始点と終点を設定した場合、無効化される)
	 * @History		24/09/16 作成(Suzuki N)
	 */
	float height;

	/**
	 * @brief		コライダーの半径
	 * @History		24/09/16 作成(Suzuki N)
	 */
	float radius;

	/**
	 * @brief		コライダーの始点
	 * @History		24/09/16 作成(Suzuki N)
	 */
	VECTOR UsStartPos;

	/**
	 * @brief		コライダーの終点
	 * @History		24/09/16 作成(Suzuki N)
	 */
	VECTOR UsEndPos;


private:

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

private:



#pragma region 押し出し処理

	/**
	 * @brief		ボックスタイプのオブジェクトと衝突した際にめり込まなくする処理
	 * @author		Suzuki N
	 * @date		24/09/26
	 */
	void PushOut_Capsule_Box(HWCollider& other);

	/**
	 * @brief		カプセルタイプのオブジェクトと衝突した際にめり込まなくする処理
	 * @author		Suzuki N
	 * @date		24/09/26
	 */
	void PushOut_Capsule_Capsule(HWCapsuleCollider& other);

	/**
	 * @brief		スフィアタイプのオブジェクトと衝突した際にめり込まなくする処理
	 * @author		Suzuki N
	 * @date		24/09/26
	 */
	void PushOut_Capsule_Sphere(HWCollider& other);

#pragma endregion

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

