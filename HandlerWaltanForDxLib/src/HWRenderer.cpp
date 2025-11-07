#include "h/HWRenderer.h"


/**
* @author   NZ
* @date     24/08/25
* @note		HWRendererの実装ファイル
*/


#pragma region コンストラクタ


HWRenderer::HWRenderer(const int _modelHandle)
{
	priority = -20;

	// コピー元のロードが終了するまで待機
	while(CheckHandleASyncLoad(_modelHandle)){}

	// 既存のモデルハンドルから複製したモデルを使う
	modelHandle = MV1DuplicateModel(_modelHandle);
}

HWRenderer::HWRenderer(const std::string& _pass)
{
	modelHandle = MV1LoadModel(_pass.c_str());
	priority = -20;
}

HWRenderer::~HWRenderer()
{
	MV1DeleteModel(modelHandle);
}


#pragma endregion

#pragma region privateメソッド




#pragma endregion

#pragma region publicメソッド





#pragma endregion


#pragma region オーバーライドメソッド


void HWRenderer::Start()
{
}

void HWRenderer::LateUpdate()
{
	if (modelHandle == -1 || CheckHandleASyncLoad(modelHandle))
	{
		return;
	}

	// HWTransformのグローバル変換行列を参照してモデルに適用
	MV1SetMatrix(modelHandle, transform->globalMat);
	// モデルを描画
	MV1DrawModel(modelHandle);
}


#pragma endregion
