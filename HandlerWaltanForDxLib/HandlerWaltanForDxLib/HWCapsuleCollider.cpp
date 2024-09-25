#include "h/HWCapsuleCollider.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		HWCapsuleColliderの実装ファイル
*/


#pragma region privateメソッド




#pragma endregion

#pragma region publicメソッド


HWCapsuleCollider::HWCapsuleCollider()
{
	colliderType = ColliderType::Capsule;	
}


#pragma endregion

#pragma region protectedメソッド




#pragma endregion

#pragma region オーバーライドメソッド


HWCapsuleCollider::~HWCapsuleCollider()
{
	CollisionWaltan::Instance().UnRegister(dynamic_cast<HWCollider*>(this));
}

void HWCapsuleCollider::DrawCollider()
{
	DrawCapsule3D(startPos, endPos, radius, GetColor(0, 255, 0), GetColor(0, 255, 0), 12, FALSE);
}

void HWCapsuleCollider::SetCollider()
{
	// 回転行列の作成（Z -> Y -> X の順）
	MATRIX rotX = MGetRotX((float)Deg2Rad(transform->rotate.x));
	MATRIX rotY = MGetRotY((float)Deg2Rad(transform->rotate.y));
	MATRIX rotZ = MGetRotZ((float)Deg2Rad(transform->rotate.z));
	mRotate = MMult(rotZ, MMult(rotY, rotX));

	//! 平行移動用の行列(原点からの移動量)
	MATRIX trans = MGetTranslate(center);
	//! trans -> rotate で掛けることで回転後に平行移動する(ローカルな平行移動)
	MATRIX mat = MMult(trans, mRotate);

	// 各頂点に回転行列を適用し、ワールド座標へ変換
	// ローカル座標での回転
	// 始点
	startPos = VTransform(startPos, mat);
	// ワールド座標への変換
	startPos = VAdd(startPos, transform->position);
	// 終点
	endPos = VTransform(endPos, mat);
	// ワールド座標への変換
	endPos = VAdd(endPos, transform->position);


	// 回転行列の作成（Z -> Y -> X の順）
	rotX = MGetRotX((float)Deg2Rad(transform->rotate.x));
	rotY = MGetRotY((float)Deg2Rad(transform->rotate.y));
	rotZ = MGetRotZ((float)Deg2Rad(transform->rotate.z));
	MATRIX mRotate2 = MMult(rotX, MMult(rotY, rotZ));
	//! 平行移動用の行列(原点からの移動量)
	trans = MGetTranslate(center);
	//! trans -> rotate で掛けることで回転後に平行移動する(ローカルな平行移動)
	mat = MMult(trans, mRotate);
	// コライダーの中心座標を更新
	worldPosition = VTransform(VGet(0, 0, 0), mat);
	worldPosition = VAdd(worldPosition, transform->position);
}


void HWCapsuleCollider::Awake()
{
	center = VGet(0, 0, 0);
	startPos = VGet(0, 50, 0);
	endPos = VGet(0, -50, 0);

	// コライダーの形を構成する
	SetCollider();

	// CollisionWaltanに登録
	CollisionWaltan::Instance().ColVec.push_back(dynamic_cast<HWCollider*>(this));
}

void HWCapsuleCollider::Update()
{
	// コライダーの形を構成する
	SetCollider();

	// デバッグモード、もしくはコライダーの可視化フラグが立っているなら、コライダーを描画する
	if (isVisualization || HandlerWaltan::debugMode)
		DrawCollider();
}


#pragma endregion