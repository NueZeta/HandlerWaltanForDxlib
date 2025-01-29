#include "h/HWModelCollider.h"


/**
* @author   Suzuki N
* @date     24/10/17
* @note		HWModelColliderの実装ファイル
*/


#pragma region privateメソッド




#pragma endregion

#pragma region publicメソッド


HWModelCollider::HWModelCollider()
{
	colliderType = ColliderType::Model;
}

HWModelCollider::~HWModelCollider()
{
}


#pragma endregion

#pragma region protectedメソッド




#pragma endregion

#pragma region オーバーライドメソッド


void HWModelCollider::DrawCollider()
{
}

void HWModelCollider::SetCollider()
{
}

void HWModelCollider::Awake()
{
}

void HWModelCollider::Update()
{
}


#pragma endregion
