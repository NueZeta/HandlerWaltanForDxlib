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

void HWBoxCollider::SetCollider()
{
	// ローカル座標での頂点座標設定
	// [0][] = 底面, [1][] = 上底
	// [][0] = 左上, [][1] = 右上, [][2] = 左下, [][3] = 右下
	vertex[0][0] = VGet(-size.x / 2, size.y / 2, -size.z / 2);
	vertex[0][1] = VGet(size.x / 2, size.y / 2, -size.z / 2);
	vertex[0][2] = VGet(-size.x / 2, size.y / 2, size.z / 2);
	vertex[0][3] = VGet(size.x / 2, size.y / 2, size.z / 2);
	vertex[1][0] = VGet(-size.x / 2, -size.y / 2, -size.z / 2);
	vertex[1][1] = VGet(size.x / 2, -size.y / 2, -size.z / 2);
	vertex[1][2] = VGet(-size.x / 2, -size.y / 2, size.z / 2);
	vertex[1][3] = VGet(size.x / 2, -size.y / 2, size.z / 2);

	// 回転行列の作成（Z → Y → X の順）
	MATRIX rotZ = MGetRotZ(transform->rotate.z);
	MATRIX rotY = MGetRotY(transform->rotate.y);
	MATRIX rotX = MGetRotX(transform->rotate.x);
	MATRIX rot = MMult(rotZ, MMult(rotY, rotX));

	// 各頂点に回転行列を適用し、ワールド座標へ変換
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			// ローカル座標での回転
			vertex[i][j] = VTransform(vertex[i][j], rot);
			// ワールド座標への変換
			vertex[i][j] = VAdd(vertex[i][j], transform->position);
		}
	}
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

	// コライダーの中心座標を更新
	worldPosition = VAdd(transform->position, center);

	// コライダーの形を構成する
	SetCollider();

	// デバッグモード、もしくはコライダーの可視化フラグが立っているなら、コライダーを描画する
	if (isVisualization || HandlerWaltan::debugMode)
		DrawCollider();
}


#pragma endregion

