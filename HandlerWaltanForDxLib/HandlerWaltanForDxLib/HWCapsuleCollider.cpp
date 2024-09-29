#include "h/HWCapsuleCollider.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		HWCapsuleColliderの実装ファイル
*/


#pragma region privateメソッド


#pragma region 押し出し処理

void HWCapsuleCollider::PushOut_Capsule_Box(HWCollider& other)
{
}

void HWCapsuleCollider::PushOut_Capsule_Capsule(HWCapsuleCollider& other)
{
}

void HWCapsuleCollider::PushOut_Capsule_Sphere(HWCollider& other)
{
}

#pragma endregion


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
	DrawCapsule3D(startPos, endPos, radius,
		6, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
}

void HWCapsuleCollider::SetCollider()
{
	startPos = VGet(0, 0, 0);
	endPos = VGet(0, height, 0);

	// 回転行列の作成（Z -> Y -> X の順）
	MATRIX rotX = MGetRotX((float)Deg2Rad(transform->rotate.x));
	MATRIX rotY = MGetRotY((float)Deg2Rad(transform->rotate.y));
	MATRIX rotZ = MGetRotZ((float)Deg2Rad(transform->rotate.z));
	mRotate = MMult(rotZ, MMult(rotY, rotX));

	//! 平行移動用の行列(原点からの移動量)
	MATRIX trans = MGetTranslate(center);
	//! trans -> rotate で掛けることで回転後に平行移動する(ローカルな平行移動)
	MATRIX mat = MMult(trans, mRotate);

	// ローカル座標での回転
	startPos = VTransform(startPos, mat);
	// ワールド座標への変換
	startPos = VAdd(startPos, transform->position);
	// ローカル座標での回転
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
	priority = -10;
	center = VGet(0, 0, 0);
	radius = 50.f;

	UsStartPos = VGet(0, 0, 0);
	UsEndPos = VGet(0, 0, 0);

	// コライダーの形を構成する
	SetCollider();

	// CollisionWaltanに登録
	CollisionWaltan::Instance().ColVec.push_back(dynamic_cast<HWCollider*>(this));
}

void HWCapsuleCollider::Update()
{
	// コライダーの始点か終点を設定していない場合は自動でキャラクターに追従するようにする
	if ((UsStartPos.x == 0.f && UsStartPos.y == 0.f && UsStartPos.z == 0.f) &&
		(UsEndPos.x == 0.f && UsEndPos.y == 0.f && UsEndPos.z == 0.f))
		// コライダーの形を構成する
		SetCollider();
	// どちらかが設定されている場合はそのまま上書き
	else
	{
		startPos = UsStartPos;
		endPos = UsEndPos;
	}

	// デバッグモード、もしくはコライダーの可視化フラグが立っているなら、コライダーを描画する
	if (isVisualization || HandlerWaltan::debugMode)
		DrawCollider();
}

void HWCapsuleCollider::OnCollisionEnter(HWCollider& _collider)
{
	//! コライダーをカプセルにキャスト
	switch (_collider.GetColliderType())
	{
	case ColliderType::Box:
		PushOut_Capsule_Box(static_cast<HWBoxCollider&>(_collider));
		break;

	case ColliderType::Capsule:
		PushOut_Capsule_Capsule(static_cast<HWCapsuleCollider&>(_collider));
		break;

	case ColliderType::Sphere:
		PushOut_Capsule_Sphere(static_cast<HWSphereCollider&>(_collider));
		break;
	}
}


#pragma endregion