#pragma once
#include "HWComponent.h"
#include "HWTransform.h"

/**
* @author   NZ
* @date     25/03/04
* @note		画像描画コンポーネントの定義
*/


/**
 * @class	ImageRenderType
 * @brief	画像描画のタイプ
 */
enum class ImageRenderType
{
	//! 通常描画
	Default,
	//! カスタム
	Custom,
};


/**
 * @class	HWImage
 * @brief	画像描画コンポーネントの定義
 */
class HWImage : public HWComponent
{
	//
	// メンバ変数
	//

public:

	//! 描画タイプ
	ImageRenderType renderType;
	//! 画像ハンドル
	int graphHandle;
	//! 透過処理を行うか
	bool isTrans;
	
private:
	
	std::function<void()> customRenderFunction;
 

	//
	// メソッド
	//

public:

	/**
	 * @brief		コンストラクタ
	 * @param[in]	画像のPath
	 */
	HWImage(const std::string& _path, ImageRenderType _renderType = ImageRenderType::Default);

	/**
	 * @brief		デストラクタ
	 */
	~HWImage();

	/**
	 * @brief		描画方法を指定
	 * @param		描画関数の指定
	 */
	void SetRenderFunction(std::function<void()> _customRenderFunction)
	{
		customRenderFunction = _customRenderFunction;
	}

	/**
	 * @brief		更新処理
	 */
	void LateUpdate()override;
};


