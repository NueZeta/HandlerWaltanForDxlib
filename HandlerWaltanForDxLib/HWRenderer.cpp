#include "h/HWRenderer.h"


/**
* @author   Suzuki N
* @date     24/08/25
* @note		HWRendererの実装ファイル
*/


#pragma region コンストラクタ


HWRenderer::HWRenderer(int _modelHandle) : modelHandle(_modelHandle)
{
}


#pragma endregion

#pragma region privateメソッド




#pragma endregion

#pragma region publicメソッド





#pragma endregion


#pragma region オーバーライドメソッド


void HWRenderer::Update()
{
	auto transform = gameObject->GetComponent<HWTransform>();
	MV1SetPosition(modelHandle, transform->GetPosition());
}


#pragma endregion
