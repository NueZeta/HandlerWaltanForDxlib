#pragma once
#include "HWComponent.h"


/**
* @author   Suzuki N
* @date     24/07/18
* @note		あたり判定の情報を保持するコンポーネントの定義
*/


/**
 * @enum		eColliderType
 * @brief		コライダータイプ
 */
enum class HWColliderType
{
	//! 四角形型のあたり判定(0)
	BoxCollider,
	//! 球形型のあたり判定(1)
	SphereCollider,
	//! カプセル型のあたり判定(2)
	CapsuleCollider,
};


/**
 * @class		HWCollider
 * @brief		あたり判定の情報を保持するコンポーネント
 */
class HWCollider : public HWComponent
{
private:


public:
	/*     メンバ変数     */

	/**
	 * @brief		コライダータイプ
	 * @History		24/07/18 作成(Suzuki N)
	 */
	HWColliderType colliderType;



	/*     メソッド     */


	/**
	 * @brief		HWColliderのコンストラクタ
	 * @detail		イニシャライズ用
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	HWCollider() : colliderType(HWColliderType::BoxCollider)
	{
	}


#pragma region オーバーライドメソッド

	/**
	 * @brief		衝突を検知したときに一度呼ばれるメソッド
	 * @detail		オーバーライド関数
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void OnCollisionEnter() override;

#pragma endregion
};
