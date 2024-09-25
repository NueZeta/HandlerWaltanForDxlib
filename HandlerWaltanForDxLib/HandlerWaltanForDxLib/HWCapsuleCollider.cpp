#include "h/HWCapsuleCollider.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		HWCapsuleColliderの実装ファイル
*/


#pragma region privateメソッド


void HWCapsuleCollider::ClosestPointsOnLineSegments(const HWCapsuleCollider& other, VECTOR& outPoint1, VECTOR& outPoint2)
{
	VECTOR u = VSub(endPos, startPos); // thisカプセルの線分ベクトル
	VECTOR v = VSub(other.endPos, other.startPos); // otherカプセルの線分ベクトル
	VECTOR w = VSub(startPos, other.startPos);

	float a = VDot(u, u); // u・u
	float b = VDot(u, v); // u・v
	float c = VDot(v, v); // v・v
	float d = VDot(u, w); // u・w
	float e = VDot(v, w); // v・w
	float denom = a * c - b * b; // 分母

	float s, t;

	// denomがゼロに近い場合（平行に近い場合）の処理
	if (denom < 1e-6f) {
		s = 0.0f;
		t = (e > 0.0f ? 0.0f : (e < 0.0f ? 1.0f : 0.0f)); // 他のカプセル上で最も近い端点を取る
	}
	else {
		s = (b * e - c * d) / denom;
		t = (a * e - b * d) / denom;

		// sが範囲外の場合の修正
		if (s < 0.0f) s = 0.0f;
		else if (s > 1.0f) s = 1.0f;

		// tが範囲外の場合の修正
		if (t < 0.0f) t = 0.0f;
		else if (t > 1.0f) t = 1.0f;
	}

	// 最近接点を求める
	outPoint1 = VAdd(startPos, VScale(u, s)); // thisカプセル上の最近接点
	outPoint2 = VAdd(other.startPos, VScale(v, t)); // otherカプセル上の最近接点
}

#pragma region 押し出し処理

void HWCapsuleCollider::PushOut_Capsule_Box(HWCollider& other)
{
}

void HWCapsuleCollider::PushOut_Capsule_Capsule(HWCapsuleCollider& other)
{
	// 2つのカプセル間の最近接点を求める
	VECTOR point1, point2;
	ClosestPointsOnLineSegments(other, point1, point2);
	VECTOR collisionVector = VSub(point2, point1);
	float distance = VSize(collisionVector);

	// 正規化された衝突ベクトル
	VECTOR collisionNormal = VScale(collisionVector, 1.0f / distance);

	// めり込み量を計算
	float penetrationDepth = (radius + other.radius) - distance;

	// カプセルの位置を修正（めり込みを解消）
	VECTOR correction = VScale(collisionNormal, penetrationDepth * 0.5f);
	startPos = VSub(startPos, correction);
	endPos = VSub(endPos, correction);
	other.startPos = VAdd(other.startPos, correction);
	other.endPos = VAdd(other.endPos, correction);

	// 衝突後の速度を調整（シンプルな反射処理）
	VECTOR relativeVelocity = VSub(other.transform->velocity, transform->velocity);
	float velocityAlongNormal = VDot(relativeVelocity, collisionNormal);

	if (velocityAlongNormal > 0) {
		return; // 速度が衝突方向に進んでいない場合は何もしない
	}

	// 反発係数（1.0だと完全弾性衝突）
	float restitution = 0.8f;

	// 衝突後の速度の計算
	float impulse = -(1.0f + restitution) * velocityAlongNormal;
	VECTOR impulseVector = VScale(collisionNormal, impulse);

	// 各カプセルの速度を更新
	transform->velocity = VAdd(transform->velocity, VScale(impulseVector, 0.5f));
	other.transform->velocity = VSub(other.transform->velocity, VScale(impulseVector, 0.5f));
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
	center = VGet(0, 0, 0);
	radius = 50.f;

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