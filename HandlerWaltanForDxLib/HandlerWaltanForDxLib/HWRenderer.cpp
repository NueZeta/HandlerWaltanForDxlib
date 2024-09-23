#include "h/HWRenderer.h"


/**
* @author   Suzuki N
* @date     24/08/25
* @note		HWRendererの実装ファイル
*/


#pragma region コンストラクタ


HWRenderer::HWRenderer(const int _modelHandle) : modelHandle(_modelHandle)
{
}

HWRenderer::HWRenderer(const std::string& _pass)
{
	modelHandle = MV1LoadModel(_pass.c_str());
}


#pragma endregion

#pragma region privateメソッド




#pragma endregion

#pragma region publicメソッド





#pragma endregion


#pragma region オーバーライドメソッド


void HWRenderer::Update()
{
	if (modelHandle == -1)
	{
		return;
	}

	// HWTransformのグローバル変換行列を参照してモデルに適用
	MV1SetMatrix(modelHandle, transform->globalMat);
	// モデルを描画
	MV1DrawModel(modelHandle);
}


#pragma endregion
