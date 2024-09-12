#include"h/HWTransform.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		MyTransformの実装ファイル
*/


#pragma region privateメソッド


#pragma endregion

#pragma region publicメソッド


HWTransform::HWTransform()
{
	position = { 0.0f, 0.0f, 0.0f };
	rotate = { 0.0f, 0.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	localPosition = { 0.0f, 0.0f, 0.0f };
	localRotate = { 0.0f, 0.0f, 0.0f };
	localScale = { 1.0f, 1.0f, 1.0f };
}


#pragma endregion

#pragma region オーバーライドメソッド


void HWTransform::Update()
{
}


#pragma endregion