#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"


/**
* @author   Suzuki N
* @date     24/08/25
* @note		モデル描画コンポーネントの定義
*/


/**
 * @class		HWRenderer
 * @brief		モデル描画用のコンポーネント
 */
class HWRenderer : public HWComponent
{
private:

	/*     メンバ変数     */

	/**
	 * @brief		モデルハンドル
	 * @History		24/08/25 作成(Suzuki N)
	 */
	int modelHandle;


public:

	/*     メソッド     */

	/**
	 * @brief		HWRendererのコンストラクタ
	 * @param[in]	int モデルハンドル
	 * @author		Suzuki N
	 * @date		24/08/25
	 */
	HWRenderer(int _modelHandle);

#pragma region オーバーライドメソッド

	/**
	 * @brief		毎フレーム呼ばれる
	 * @detail		オーバーライド関数
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	void Update() override;

#pragma endregion
};

