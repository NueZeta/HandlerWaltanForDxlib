#pragma once
#include "HWComponent.h"


/**
* @author   Suzuki N
* @date     24/07/16
* @note		座標系の情報を保持するコンポーネントの定義
*/


/**
 * @class		HWTransform
 * @brief		オブジェクトの座標や回転などを保持するコンポーネント
 */
class HWTransform : public HWComponent
{
private:


public:
	/*     メンバ変数     */

	/**
	 * @brief		ワールド座標
	 * @History		24/06/17 作成(Suzuki N)
	 */
	VECTOR Position;


	/*     メソッド     */

#pragma region コンストラクタ

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	HWTransform();

#pragma endregion


#pragma region Getterメソッド群

	/**
	 * @brief		ワールド座標を返す
	 * @return		ワールド座標
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	VECTOR GetPosition() { return Position; }

#pragma endregion

#pragma region オーバーライドメソッド

	/**
	 * @brief		毎フレーム呼ばれる
	 * @detail		オーバーライド関数
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void Update() override;

#pragma endregion
};
