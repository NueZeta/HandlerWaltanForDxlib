#include "h/CollisionWaltan.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		ColliderWaltanの実装ファイル
*/


#pragma region publucメソッド



#pragma endregion

#pragma region privateメソッド


CollisionWaltan::CollisionWaltan()
{

}


CollisionWaltan::~CollisionWaltan()
{

}

void CollisionWaltan::Update()
{
	// 当たり判定をチェックする
	// チェックの重複をなくすため、最後の要素から-1した要素までにする
	for (auto it1 = ColVec.begin(); it1 != ColVec.end() - 1; ++it1)
	{
		// すでにチェックした組み合わせを省く
		for (auto it2 = it1 + 1; it2 != ColVec.end(); ++it2)
		{
			// it1 のコライダータイプによって処理を変える
			switch ((*it1)->GetColliderType())
			{
				// 立方体型コライダーの場合
			case ColliderType::Box:
				if (CollCheck_Box(dynamic_cast<HWBoxCollider*>(*it1), *it2))
					(*it1)->gameObject->CallAllOnCollisionEnters(*it2);
					(*it2)->gameObject->CallAllOnCollisionEnters(*it1);
				break;
				// カプセル型コライダーの場合
			case ColliderType::Capsule:
				CollCheck_Capsule(dynamic_cast<HWCapsuleCollider*>(*it1), *it2);
				break;
				// 球体型コライダーの場合
			case ColliderType::Sphere:
				CollCheck_Sphere(dynamic_cast<HWSphereCollider*>(*it1), *it2);
				break;
			}
		}
	}
}

bool CollisionWaltan::CollCheck_Box(HWBoxCollider* _col1, HWCollider* _col2)
{
	// _col2のコライダータイプによって処理を変える
	switch (_col2->GetColliderType())
	{
		// 立方体型コライダーの場合
	case ColliderType::Box:
	{
		HWBoxCollider* boxCol = dynamic_cast<HWBoxCollider*>(_col2);

		if (fabs(_col1->worldPosition.x - boxCol->worldPosition.x) > (_col1->size.x / 2 + boxCol->size.x / 2)) return false;
		if (fabs(_col1->worldPosition.y - boxCol->worldPosition.y) > (_col1->size.y / 2 + boxCol->size.y / 2)) return false;
		if (fabs(_col1->worldPosition.z - boxCol->worldPosition.z) > (_col1->size.z / 2 + boxCol->size.z / 2)) return false;

		return true;
		break;
	}
	// カプセル型コライダーの場合
	case ColliderType::Capsule:
	{
		HWCapsuleCollider* capsuleCol = dynamic_cast<HWCapsuleCollider*>(_col2);
		break;
	}
	// 球体型コライダーの場合
	case ColliderType::Sphere:
	{
		HWSphereCollider* sphereCol = dynamic_cast<HWSphereCollider*>(_col2);
		break;
	}
	}

	return false;
}

bool CollisionWaltan::CollCheck_Sphere(HWSphereCollider* _col1, HWCollider* _col2)
{
	// _col2のコライダータイプによって処理を変える
	switch (_col2->GetColliderType())
	{
		// 立方体型コライダーの場合
	case ColliderType::Box:
		break;
		// カプセル型コライダーの場合
	case ColliderType::Capsule:
		break;
		// 球体型コライダーの場合
	case ColliderType::Sphere:
		break;
	}

	return false;
}

bool CollisionWaltan::CollCheck_Capsule(HWCapsuleCollider* _col1, HWCollider* _col2)
{
	// _col2のコライダータイプによって処理を変える
	switch (_col2->GetColliderType())
	{
		// 立方体型コライダーの場合
	case ColliderType::Box:
		break;
		// カプセル型コライダーの場合
	case ColliderType::Capsule:
		break;
		// 球体型コライダーの場合
	case ColliderType::Sphere:
		break;
	}

	return false;
}

#pragma endregion

