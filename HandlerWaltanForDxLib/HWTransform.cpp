#include"h/HWTransform.h"


/**
* @author   NZ
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
	// ENEMY -> Player への方向ベクトルを計算
	VECTOR dir = VNorm(VSub(_target, position));

	// 内積を使ってベクトル間の角度を計算
	float dot = VDot(forward, dir);

	// acosf を使う前にクリッピング（誤差対策）
	if (dot < -1.0f) dot = -1.0f;
	if (dot > 1.0f) dot = 1.0f;

	// なす角を計算
	float angle = acosf(dot);

	// 外積を用いて回転軸を求める
	VECTOR axis = VCross(forward, dir);

	// 外積がゼロベクトルでないかをチェック（ほぼ同じ方向の場合、外積はゼロになる）
	if (VSize(axis) > 0.0001f) {
		axis = VNorm(axis);

		// 回転に適用
		rotate.x += (float)Rad2Deg(axis.x * angle);
		rotate.y += (float)Rad2Deg(axis.y * angle);
		rotate.z += (float)Rad2Deg(axis.z * angle);
	}
	else {
		// 回転軸が無効な場合、処理をスキップまたは代替処理
		// 例：ほぼ同じ方向に向いているので、回転は必要ない
	}
}

HWTransform::HWTransform() : position({ 0.0f, 0.0f, 0.0f }), rotate({ 0.0f, 0.0f, 0.0f }),
scale({ 1.0f, 1.0f, 1.0f }), localPosition({ 0.0f, 0.0f, 0.0f }), localRotate({ 0.0f, 0.0f, 0.0f }),
localScale({ 1.0f, 1.0f, 1.0f }), previousPosition(position)
{
	priority = 20;
	globalMat = MGetIdent();
}


#pragma endregion

#pragma region オーバーライドメソッド


void HWTransform::Update()
{
	// positionを操作した場合の移動量をvelocityに足す
	velocity = VAdd(velocity, VSub(position, previousPosition));

	// 座標に移動ベクトルを足す
	position = VAdd(previousPosition, velocity);

	// 親オブジェクトの影響を子に与える
	if (gameObject->isAffect)
	{
		// 親オブジェクトが存在する場合、親の行列を子に適用
		if (gameObject->Parent() != nullptr)
		{
			// 親のグローバル行列を取得
			MATRIX parentMatrix = gameObject->Parent()->transform->globalMat;

			// 子のローカル行列に親の行列を掛ける
			globalMat = MMult(globalMat, parentMatrix);
		}
	}
	// 子オブジェクトに親の変換を適用
	if (gameObject->GetChildren().size() > 0)
		for (auto it = gameObject->GetChildren().begin(); it != gameObject->GetChildren().end(); ++it)
			if((*it)->isAffect)	(*it)->transform->velocity = VAdd((*it)->transform->velocity, velocity);

	// 移動ベクトルの初期化
	velocity = VGet(0, 0, 0);
	// 前Fの座標を更新
	previousPosition = position;

	SetMatrix();
}


#pragma endregion