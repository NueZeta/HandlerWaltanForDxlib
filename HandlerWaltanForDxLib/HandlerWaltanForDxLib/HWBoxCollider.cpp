#include "h/HWBoxCollider.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		HWBoxColliderの実装ファイル
*/


#pragma region privateメソッド




#pragma endregion

#pragma region publicメソッド


HWBoxCollider::HWBoxCollider()
{
	colliderType = ColliderType::Box;
	size = VGet(50.f, 50.f, 50.f);
}

HWBoxCollider::HWBoxCollider(VECTOR _size) : size(_size)
{
	colliderType = ColliderType::Box;
}

HWBoxCollider::HWBoxCollider(float _sizeX, float _sizeY, float _sizeZ) : size(VGet(_sizeX, _sizeY, _sizeZ))
{
	colliderType = ColliderType::Box;
}


#pragma endregion

#pragma region protectedメソッド




#pragma endregion

#pragma region オーバーライドメソッド


HWBoxCollider::~HWBoxCollider()
{
	CollisionWaltan::Instance().UnRegister(dynamic_cast<HWCollider*>(this));
}

void HWBoxCollider::DrawCollider()
{
	//! 頂点座標
	// [0][] = 底面, [1][] = 上底
	// [][0] = 左上, [][1] = 右上, [][2] = 左下, [][3] = 右下
	VECTOR vertex[2][4];

	vertex[0][0] = VAdd(worldPosition, VGet(-size.x / 2, size.y / 2, -size.z / 2));
	vertex[0][1] = VAdd(worldPosition, VGet(size.x / 2, size.y / 2, -size.z / 2));
	vertex[0][2] = VAdd(worldPosition, VGet(-size.x / 2, size.y / 2, size.z / 2));
	vertex[0][3] = VAdd(worldPosition, VGet(size.x / 2, size.y / 2, size.z / 2));
	vertex[1][0] = VAdd(worldPosition, VGet(-size.x / 2, -size.y / 2, -size.z / 2));
	vertex[1][1] = VAdd(worldPosition, VGet(size.x / 2, -size.y / 2, -size.z / 2));
	vertex[1][2] = VAdd(worldPosition, VGet(-size.x / 2, -size.y / 2, size.z / 2));
	vertex[1][3] = VAdd(worldPosition, VGet(size.x / 2, -size.y / 2, size.z / 2));


	DrawLine3D(vertex[0][0], vertex[0][1], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][0], vertex[0][2], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][1], vertex[0][3], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][2], vertex[0][3], GetColor(0, 255, 0));
	
	DrawLine3D(vertex[0][0], vertex[1][0], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][1], vertex[1][1], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][2], vertex[1][2], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][3], vertex[1][3], GetColor(0, 255, 0));

	DrawLine3D(vertex[1][0], vertex[1][1], GetColor(0, 255, 0));
	DrawLine3D(vertex[1][0], vertex[1][2], GetColor(0, 255, 0));
	DrawLine3D(vertex[1][1], vertex[1][3], GetColor(0, 255, 0));
	DrawLine3D(vertex[1][2], vertex[1][3], GetColor(0, 255, 0));
}

void HWBoxCollider::Awake()
{
	center = VGet(0, 0, 0);
	worldPosition = VAdd(transform->position, center);
	// CollisionWaltanに登録
	CollisionWaltan::Instance().ColVec.push_back(dynamic_cast<HWCollider*>(this));
}

void HWBoxCollider::Update()
{
	// 回転行列の作成
	MATRIX rotX = MGetRotX(transform->rotate.x);
	MATRIX rotY = MGetRotY(transform->rotate.y);
	MATRIX rotZ = MGetRotZ(transform->rotate.z);

	MATRIX rot = MMult(rotZ, MMult(rotY, rotX));



	worldPosition = VAdd(transform->position, center);

	// デバッグモード、もしくはコライダーの可視化フラグが立っているなら、コライダーを描画する
	if (isVisualization || HandlerWaltan::debugMode)
		DrawCollider();
}


#pragma endregion

