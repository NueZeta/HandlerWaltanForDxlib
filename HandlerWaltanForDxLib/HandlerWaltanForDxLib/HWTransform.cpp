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
	MATRIX rotX = MGetRotX((float)Deg2Rad(rotate.x));
	MATRIX rotY = MGetRotY((float)Deg2Rad(rotate.y));
	MATRIX rotZ = MGetRotZ((float)Deg2Rad(rotate.z));
	// グローバル回転
	rot = MMult(rotZ, MMult(rotY, rotX));
	// ローカル回転
	//rot = MMult(rotX, MMult(rotY, rotZ));

	// 拡縮
	scl = MGetScale(scale);

	// 最後に行列をかけ合わせる
	globalMat = MMult(scl, MMult(rot, pos));


	// 正面ベクトルを更新
	forward = VTransform(VGet(0, 0, -1), rot);
	// ベクトルを正規化
	forward = VNorm(forward);
}


#pragma endregion

#pragma region publicメソッド


void HWTransform::LookAt(const VECTOR& _target)
{
	//! ENEMY -> Player への方向ベクトル
	VECTOR dir = VNorm(VSub(_target, position));
	//! 内積を使ってベクトル間の角度を計算
	float dot = VDot(forward, dir);
	//! なす角
	float angle = acosf(dot);
	//! 外積を用いて回転軸を求める
	VECTOR axis = VNorm(VCross(forward, dir));
	// 回転に適用
	rotate.x += (float)Rad2Deg(axis.x * angle);
	rotate.y += (float)Rad2Deg(axis.y * angle);
	rotate.z += (float)Rad2Deg(axis.z * angle);
}

HWTransform::HWTransform() : position({ 0.0f, 0.0f, 0.0f }), rotate({ 0.0f, 0.0f, 0.0f }),
scale({ 1.0f, 1.0f, 1.0f }), localPosition({ 0.0f, 0.0f, 0.0f }), localRotate({ 0.0f, 0.0f, 0.0f }),
localScale({ 1.0f, 1.0f, 1.0f })
{
	priority = 20;
	globalMat = MGetIdent();
}


#pragma endregion

#pragma region オーバーライドメソッド


void HWTransform::Update()
{
	// 座標に移動ベクトルを足す
	position = VAdd(position, velocity);

	// 親オブジェクトが存在する場合、親の行列を子に適用
	if (gameObject->Parent() != nullptr) 
	{
		// 親のグローバル行列を取得
		MATRIX parentMatrix = gameObject->Parent()->transform->globalMat;

		// 子のローカル行列に親の行列を掛ける
		globalMat = MMult(globalMat, parentMatrix);
	}

	// 子オブジェクトに親の変換を適用
	if (gameObject->GetChildren().size() > 0)
		for (auto it = gameObject->GetChildren().begin(); it != gameObject->GetChildren().end(); ++it)
			(*it)->transform->velocity = VAdd((*it)->transform->velocity, velocity);

	// 移動ベクトルの初期化
	velocity = VGet(0, 0, 0);

	SetMatrix();
}


#pragma endregion