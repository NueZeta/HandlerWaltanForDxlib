#include"h/HWTransform.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		MyTransformの実装ファイル
*/


#pragma region privateメソッド


void HWTransform::SetMatrix()
{
	MATRIX pos, rot, scl;

	// 平行移動
	pos = MGetTranslate(position);
	// 回転
	MATRIX rotX = MGetRotX(rotate.x);
	MATRIX rotY = MGetRotY(rotate.y);
	MATRIX rotZ = MGetRotZ(rotate.z);
	// グローバル回転
	rot = MMult(rotZ, MMult(rotY, rotX));
	// ローカル回転
	//rot = MMult(rotX, MMult(rotY, rotZ));

	// 拡縮
	scl = MGetScale(scale);

	// 最後に行列をかけ合わせる
	globalMat = MMult(scl, MMult(rot, pos));
}


#pragma endregion

#pragma region publicメソッド


HWTransform::HWTransform() : position({ 0.0f, 0.0f, 0.0f }), rotate({ 0.0f, 0.0f, 0.0f }), 
scale({ 1.0f, 1.0f, 1.0f }), localPosition({ 0.0f, 0.0f, 0.0f }), localRotate({ 0.0f, 0.0f, 0.0f }),
localScale({ 1.0f, 1.0f, 1.0f })
{
	globalMat = MGetIdent();
}


#pragma endregion

#pragma region オーバーライドメソッド


void HWTransform::Update()
{
	SetMatrix();
}


#pragma endregion