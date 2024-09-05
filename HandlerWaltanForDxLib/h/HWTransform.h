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
public:

	/*     メンバ変数     */

	/**
	 * @brief		ワールド座標
	 * @History		24/06/17 作成(Suzuki N)
	 */
	VECTOR position;

	/**
	 * @brief		回転
	 * @History		24/06/17 作成(Suzuki N)
	 */

	VECTOR rotate;

	/**
	 * @brief		拡縮
	 * @History		24/06/17 作成(Suzuki N)
	 */
	VECTOR scale;


public:

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
	VECTOR GetPosition() { return position; }

	/**
	 * @brief		回転を返す
	 * @return		回転
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	VECTOR GetRotate() { return rotate; }

	/**
	 * @brief		拡縮度を返す
	 * @return		拡縮
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	VECTOR GetScale() { return scale; }

#pragma endregion

#pragma region Setterメソッド群

	/**
	 * @brief		ワールド座標を変更
	 * @param[in]	変更後の座標
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void SetPosition(VECTOR _pos) { position = _pos; }

	/**
	 * @brief		回転を変更
	 * @param[in]	変更後の回転
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void SetRotate(VECTOR _rot) { rotate = _rot; }

	/**
	 * @brief		拡縮を変更
	 * @param[in]	変更後の拡縮
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void SetScale(VECTOR _scale) { scale = _scale; }

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
