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
	//! 登録されているColliderの数が一個以下ならそのまま終了
	if (ColVec.size() < 2)return;

	// 当たり判定をチェックする
	for (auto it1 = ColVec.begin(); it1 != ColVec.end() - 1; ++it1)
	{
		// すでにチェックした組み合わせを省く
		for (auto it2 = it1 + 1; it2 != ColVec.end(); ++it2)
		{
			// アタッチされているGameObjectが同じ場合は無視
			if ((*it1)->gameObject == (*it2)->gameObject) continue;	
			// triggerと非triggerの場合はその組み合わせは無視
			if ((*it1)->isTrigger != (*it2)->isTrigger) continue;

			// 衝突中のコライダーのリストに登録されているか調べる
			auto collisionIt = std::find((*it1)->CollidersInCollision.begin(),
				(*it1)->CollidersInCollision.end(), *it2);

			// it1 のコライダータイプによって処理を変える
			switch ((*it1)->GetColliderType())
			{
				// 立方体型コライダーの場合
			case ColliderType::Box:
				if (CollCheck_Box(dynamic_cast<HWBoxCollider*>(*it1), *it2))
					// Hit時のコールバック関数を呼び出す
					ColliderHitCallBacks(collisionIt, *it1, *it2, (*it1)->isTrigger);
				else
					// 未接触時の処理
					ColliderAvoidCallBacks(collisionIt, *it1, *it2, (*it1)->isTrigger);
				break;

				// カプセル型コライダーの場合
			case ColliderType::Capsule:
				if (!(*it1)->isTrigger && ((*it2)->gameObject->name == "Map" ||
					(*it2)->gameObject->name == "map" || (*it2)->gameObject->name == "Stage" ||
					(*it2)->gameObject->name == "stage"))
					// コライダーがtriggerではない場合、壁とのあたり判定を取る
					CollCheck_Capsule_Model(dynamic_cast<HWCapsuleCollider*>(*it1),
						(*it2)->gameObject->GetComponent<HWRenderer>()->GetModelHandle());

				if (CollCheck_Capsule(dynamic_cast<HWCapsuleCollider*>(*it1), *it2))
					// Hit時のコールバック関数を呼び出す
					ColliderHitCallBacks(collisionIt, *it1, *it2, (*it1)->isTrigger);
				else
					// 未接触時の処理
					ColliderAvoidCallBacks(collisionIt, *it1, *it2, (*it1)->isTrigger);
				break;

				// 球体型コライダーの場合
			case ColliderType::Sphere:
				CollCheck_Sphere(dynamic_cast<HWSphereCollider*>(*it1), *it2);
				break;
			}
		}
	}
}

void CollisionWaltan::UnRegister(HWCollider* _collider)
{
	// 要素を削除する
	auto it = std::find(ColVec.begin(), ColVec.end(), _collider);
	// 見つかった場合は削除
	if (it != ColVec.end())
		ColVec.erase(it);
}

bool CollisionWaltan::CollCheck_Box(HWBoxCollider* boxCol1, HWCollider* _col2)
{
	// _col2のコライダータイプによって処理を変える
	switch (_col2->GetColliderType())
	{
	// ボックス to ボックス の場合
	case ColliderType::Box:
		return CollCheck_Box_Box(boxCol1, static_cast<HWBoxCollider*>(_col2));

	// ボックス to カプセル の場合
	case ColliderType::Capsule:
		return CollCheck_Box_Capsule(boxCol1, static_cast<HWCapsuleCollider*>(_col2));

	// ボックス to スフィア の場合
	case ColliderType::Sphere:
		return CollCheck_Box_Sphere(boxCol1, static_cast<HWSphereCollider*>(_col2));
	}

	return false;
}

bool CollisionWaltan::CollCheck_Capsule(HWCapsuleCollider* _col1, HWCollider* _col2)
{
	// _col2のコライダータイプによって処理を変える
	switch (_col2->GetColliderType())
	{
		// カプセル to ボックス の場合
	case ColliderType::Box:
		return CollCheck_Capsule_Box(_col1, static_cast<HWBoxCollider*>(_col2));

		// カプセル to カプセル の場合
	case ColliderType::Capsule:
		return CollCheck_Capsule_Capsule(_col1, static_cast<HWCapsuleCollider*>(_col2));

		// カプセル to スフィア の場合
	case ColliderType::Sphere:
		return CollCheck_Capsule_Sphere(_col1, static_cast<HWSphereCollider*>(_col2));
	}

	return false;
}

bool CollisionWaltan::CollCheck_Sphere(HWSphereCollider* _col1, HWCollider* _col2)
{
	// _col2のコライダータイプによって処理を変える
	switch (_col2->GetColliderType())
	{
		// スフィア to ボックス の場合
	case ColliderType::Box:
		return CollCheck_Sphere_Box(_col1, static_cast<HWBoxCollider*>(_col2));

		// スフィア to カプセル の場合
	case ColliderType::Capsule:
		return CollCheck_Sphere_Capsule(_col1, static_cast<HWCapsuleCollider*>(_col2));

		// スフィア to スフィア の場合
	case ColliderType::Sphere:
		return CollCheck_Sphere_Sphere(_col1, static_cast<HWSphereCollider*>(_col2));
	}

	return false;
}


#pragma region BOXタイプの衝突判定


bool CollisionWaltan::CollCheck_BOX_Model(HWBoxCollider* _boxCol, const int _modelHandle)
{
	return false;
}

bool CollisionWaltan::CollCheck_Box_Box(HWBoxCollider* _boxCol, HWBoxCollider* _boxCol2)
{
	OBB obb1;
	OBB obb2;

	obb1.c = _boxCol->worldPosition;
	// 回転行列の作成（X -> Y -> Z の順）
	MATRIX rotX1 = MGetRotX((float)Deg2Rad(_boxCol->transform->rotate.x));
	MATRIX rotY1 = MGetRotY((float)Deg2Rad(_boxCol->transform->rotate.y));
	MATRIX rotZ1 = MGetRotZ((float)Deg2Rad(_boxCol->transform->rotate.z));
	MATRIX mRotate1 = MMult(rotZ1, MMult(rotY1, rotX1));

	obb1.u[0] = VGet(mRotate1.m[0][0], mRotate1.m[1][0], mRotate1.m[2][0]); // X軸
	obb1.u[1] = VGet(mRotate1.m[0][1], mRotate1.m[1][1], mRotate1.m[2][1]); // Y軸
	obb1.u[2] = VGet(mRotate1.m[0][2], mRotate1.m[1][2], mRotate1.m[2][2]); // Z軸
	obb1.e = VGet(_boxCol->size.x / 2, _boxCol->size.y / 2, _boxCol->size.z / 2);

	obb2.c = _boxCol2->worldPosition;
	// 回転行列の作成（X -> Y -> Z の順）
	MATRIX rotX2 = MGetRotX((float)Deg2Rad(_boxCol2->transform->rotate.x));
	MATRIX rotY2 = MGetRotY((float)Deg2Rad(_boxCol2->transform->rotate.y));
	MATRIX rotZ2 = MGetRotZ((float)Deg2Rad(_boxCol2->transform->rotate.z));
	MATRIX mRotate2 = MMult(rotZ2, MMult(rotY2, rotX2));
	obb2.u[0] = VGet(mRotate2.m[0][0], mRotate2.m[1][0], mRotate2.m[2][0]); // X軸
	obb2.u[1] = VGet(mRotate2.m[0][1], mRotate2.m[1][1], mRotate2.m[2][1]); // Y軸
	obb2.u[2] = VGet(mRotate2.m[0][2], mRotate2.m[1][2], mRotate2.m[2][2]); // Z軸
	obb2.e = VGet(_boxCol2->size.x / 2, _boxCol2->size.y / 2, _boxCol2->size.z / 2);

	if (!TestOBBOBB(&obb1, &obb2))
		return false;


	// コライダーがトリガーでないなら、コライダー同士がめり込まないようにする
	if (!_boxCol->isTrigger)
	{
	}

	return true;
}

bool CollisionWaltan::CollCheck_Box_Capsule(HWBoxCollider* _boxCol, HWCapsuleCollider* _capsuleCol)
{
	return false;
}

bool CollisionWaltan::CollCheck_Box_Sphere(HWBoxCollider* _boxCol, HWSphereCollider* _sphereCol)
{
	return false;
}


#pragma endregion

#pragma region CAPSULEタイプの衝突判定


bool CollisionWaltan::CollCheck_Capsule_Model(HWCapsuleCollider* _capsuleCol, const int _modelHandle)
{
	MV1_COLL_RESULT_POLY* Poly;			// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )

	// 移動前の座標を保存
	const VECTOR OldPos = _capsuleCol->transform->position;
	// 移動量
	VECTOR velocity = _capsuleCol->transform->velocity;
	// 移動後の座標を算出
	VECTOR NewPos = VAdd(OldPos, velocity);

	std::vector<MV1_COLL_RESULT_POLY*> Walls;	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	std::vector<MV1_COLL_RESULT_POLY*> Floors;	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列

	int MaxHitCol = 0;
	int HitTryNum = 0;

	bool isWallHit;

	// プレイヤーの周囲にあるステージポリゴンを取得する
	// ( 検出する範囲は移動距離も考慮する )
	MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Sphere(_modelHandle, -1, OldPos, _capsuleCol->radius);

	// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」扱い
	const bool IsMove = fabs(velocity.x) > 0.01f || fabs(velocity.z) > 0.01f;

	// 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断する
	Walls.clear();
	Floors.clear();

	// 検出されたポリゴンの数だけ繰り返し
	for (int i = 0; i < HitDim.HitNum; i++)
	{
		// ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
		if (IsNearlyZero(HitDim.Dim[i].Normal.y))
		{
			// 壁ポリゴンと判断された場合でも、プレイヤーのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
			if (HitDim.Dim[i].Position[0].y > OldPos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > OldPos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > OldPos.y + 1.0f)
			{
				// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
				if (Walls.size() < MaxHitCol)
				{
					// ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
					Walls.push_back(&HitDim.Dim[i]);
				}
			}
		}
		else
		{
			// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
			if (Floors.size() < MaxHitCol)
			{
				// ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
				Floors.push_back(&HitDim.Dim[i]);
			}
		}
	}

	// 壁ポリゴンとの当たり判定処理
	if (Walls.size() != 0)
	{
		// 移動したかどうかで処理を分岐
		if (IsMove)
		{
			// 壁ポリゴンの数だけ繰り返し
			for (int i = 0; i < Walls.size(); i++)
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				Poly = Walls[i];

				// ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
				if (HitCheck_Capsule_Triangle(NewPos, VAdd(NewPos, VGet(0.0f, _capsuleCol->height, 0.0f)), _capsuleCol->radius,
					Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) { continue; }

				// ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
				isWallHit = true;

				// 壁に当たったら壁に遮られない移動成分分だけ移動する
				{
					VECTOR SlideVec;	// プレイヤーをスライドさせるベクトル

					// 進行方向ベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出
					SlideVec = VCross(velocity, Poly->Normal);

					// 算出したベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出、これが
					// 元の移動成分から壁方向の移動成分を抜いたベクトル
					SlideVec = VCross(Poly->Normal, SlideVec);

					// それを移動前の座標に足したものを新たな座標とする
					NewPos = VAdd(OldPos, SlideVec);
				}

				// 新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
				bool isCollisionNewPos = false;
				for (int j = 0; j < Walls.size(); j++)
				{
					// j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					Poly = Walls[j];

					// 当たっていたらループから抜ける
					if (HitCheck_Capsule_Triangle(NewPos, VAdd(NewPos, VGet(0.0f, _capsuleCol->height, 0.0f)), _capsuleCol->radius,
						Poly->Position[0], Poly->Position[1], Poly->Position[2]))
					{
						isCollisionNewPos = true;
						break;
					}
				}

				// どのポリゴンとも当たらなかったので
				// 壁に当たったフラグを倒した上でループから抜ける
				if (!isCollisionNewPos)
				{
					isWallHit = false;
					break;
				}
			}
		}
		else
		{
			// 移動していない場合の処理

			// 壁ポリゴンの数だけ繰り返し
			for (int i = 0; i < Walls.size(); i++)
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				Poly = Walls[i];

				// ポリゴンに当たっていたら当たったフラグを立てた上でループから抜ける
				if (HitCheck_Capsule_Triangle(NewPos, VAdd(NewPos, VGet(0.0f, _capsuleCol->height, 0.0f)), _capsuleCol->radius,
					Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
				{
					isWallHit = true;
					break;
				}
			}
		}

		// 壁に当たっていたら壁から押し出す処理を行う
		if (isWallHit)
		{
			// 壁からの押し出し処理を試みる最大数だけ繰り返し
			for (int k = 0; k < HitTryNum; k++)
			{
				bool IsNeedHitTry = true;
				// 壁ポリゴンの数だけ繰り返し
				for (int i = 0; i < Walls.size(); i++)
				{
					// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					Poly = Walls[i];

					// プレイヤーと当たっているかを判定
					if (HitCheck_Capsule_Triangle(NewPos, VAdd(NewPos, VGet(0.0f, _capsuleCol->height, 0.0f)), _capsuleCol->radius,
						Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) { continue; }

					// 当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
					NewPos = VAdd(NewPos, VScale(Poly->Normal, HIT_SLIDE_LENGTH));

					// 移動した上で壁ポリゴンと接触しているかどうかを判定
					bool isCollisionNewPos = false;
					for (int j = 0; j < Walls.size(); j++)
					{
						// 当たっていたらループを抜ける
						Poly = Walls[j];
						if (HitCheck_Capsule_Triangle(NewPos, VAdd(NewPos, VGet(0.0f, _capsuleCol->height, 0.0f)), _capsuleCol->radius,
							Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
						{
							isCollisionNewPos = true;
							break;
						}
					}

					// 全てのポリゴンと当たっていなかったらここでループ終了
					if (!isCollisionNewPos)
					{
						// 全部のポリゴンで押し出しを試みる前に全ての壁ポリゴンと接触しなくなったということなので押し出しチェックはもうしなくていい.
						IsNeedHitTry = false;
						break;
					}
				}

				if (!IsNeedHitTry)
				{
					break;
				}
			}
		}
	}

	return isWallHit;
}

bool CollisionWaltan::CollCheck_Capsule_Box(HWCapsuleCollider* _capsuleCol, HWBoxCollider* _boxCol)
{
	return false;
}

bool CollisionWaltan::CollCheck_Capsule_Capsule(HWCapsuleCollider* _capsuleCol, HWCapsuleCollider* _capsuleCol2)
{
	VECTOR sPos1 = VAdd(_capsuleCol->startPos, _capsuleCol->transform->velocity);
	VECTOR ePos1 = VAdd(_capsuleCol->endPos, _capsuleCol->transform->velocity);
	VECTOR sPos2 = VAdd(_capsuleCol2->startPos, _capsuleCol2->transform->velocity);
	VECTOR ePos2 = VAdd(_capsuleCol2->endPos, _capsuleCol2->transform->velocity);

	if (!HitCheck_Capsule_Capsule(sPos1, ePos1, _capsuleCol->radius,
		sPos2, ePos2, _capsuleCol2->radius))
		return false;

	// コライダーがトリガーでないなら、コライダー同士がめり込まないようにする
	if (!_capsuleCol->isTrigger)
	{
		// 移動ベクトルを無効化する
		_capsuleCol->transform->velocity = VGet(0, 0, 0);
		_capsuleCol2->transform->velocity = VGet(0, 0, 0);
	}

	return true;
}

bool CollisionWaltan::CollCheck_Capsule_Sphere(HWCapsuleCollider* _capsuleCol, HWSphereCollider* _sphereCol)
{
	return false;
}


#pragma endregion

#pragma region SPHEREタイプの衝突判定


bool CollisionWaltan::CollCheck_Sphere_Model(HWSphereCollider* _sphereCol, const int _modelHandle)
{
	return false;
}

bool CollisionWaltan::CollCheck_Sphere_Box(HWSphereCollider* _sphereCol, HWBoxCollider* _boxCol)
{
	return false;
}

bool CollisionWaltan::CollCheck_Sphere_Capsule(HWSphereCollider* _sphereCol, HWCapsuleCollider* _capsuleCol)
{
	return false;
}

bool CollisionWaltan::CollCheck_Sphere_Sphere(HWSphereCollider* _sphereCol, HWSphereCollider* _sphereCol2)
{
	return false;
}


#pragma endregion


void CollisionWaltan::ColliderHitCallBacks(std::vector<HWCollider*>::iterator colIt, HWCollider* _col1, HWCollider* _col2, bool _isTrigger)
{
	// 衝突を検知した
	// コライダーがtriggerかどうかで呼ぶメソッドを変える
	if (_col1->isTrigger)
	{
		if (colIt == _col1->CollidersInCollision.end())
		{

			// 衝突時のコールバック関数の呼び出し
			_col1->gameObject->CallAllOnTriggerEnters(*_col2);
			_col2->gameObject->CallAllOnTriggerEnters(*_col1);
		}
		else
		{
			// すでに登録されている場合は衝突中のコールバック関数を呼び出す
			_col1->gameObject->CallAllOnTriggerStays(*_col2);
			_col1->gameObject->CallAllOnTriggerStays(*_col1);
		}
	}
	else
	{
		// 非triggerの場合
		if (colIt == _col1->CollidersInCollision.end())
		{

			// 衝突時のコールバック関数の呼び出し
			_col1->gameObject->CallAllOnCollisionEnters(*_col2);
			_col2->gameObject->CallAllOnCollisionEnters(*_col1);
		}
		else
		{
			// すでに登録されている場合は衝突中のコールバック関数を呼び出す
			_col1->gameObject->CallAllOnCollisionStays(*_col2);
			_col2->gameObject->CallAllOnCollisionStays(*_col1);
		}
	}
	// 衝突中のコライダーのリストにない場合は新たに登録
	if (colIt == _col1->CollidersInCollision.end())
	{
		_col1->CollidersInCollision.push_back(_col2);
		_col2->CollidersInCollision.push_back(_col1);
	}
}

void CollisionWaltan::ColliderAvoidCallBacks(std::vector<HWCollider*>::iterator colIt, HWCollider* _col1, HWCollider* _col2, bool _isTrigger)
{
	// 衝突を検知しなかった
	// 登録しているコライダーの場合(前フレームまで衝突していた)
	if (colIt != _col1->CollidersInCollision.end())
	{
		// コライダーがtriggerかどうかで呼ぶメソッドを変える
		if (_col1->isTrigger)
		{
			// 衝突終了時のコールバック関数の呼び出し
			_col1->gameObject->CallAllOnTriggerExits(*_col2);
			_col2->gameObject->CallAllOnTriggerExits(*_col1);
		}
		else
		{
			// 非triggerの場合
			// 衝突終了時のコールバック関数の呼び出し
			_col1->gameObject->CallAllOnCollisionExits(*_col2);
			_col2->gameObject->CallAllOnCollisionExits(*_col1);
		}
		// 登録情報を削除する
		_col1->CollidersInCollision.erase(colIt);
		auto collisionIt2 = std::find(_col2->CollidersInCollision.begin(),
			_col2->CollidersInCollision.end(), _col1);
		if (collisionIt2 != _col2->CollidersInCollision.end())
			_col2->CollidersInCollision.erase(collisionIt2);
	}
}

int CollisionWaltan::TestOBBOBB(OBB* a, OBB* b)
{
	const float EPSILON = 1.175494e-37f;

	float R[3][3], AbsR[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			R[i][j] = VDot(a->u[i], b->u[j]);
			AbsR[i][j] = fabsf(R[i][j]) + EPSILON;
		}
	}

	VECTOR t = VSub(b->c, a->c);
	t = VGet(VDot(t, a->u[0]), VDot(t, a->u[1]), VDot(t, a->u[2]));

	//軸L=A0, L=A1, L=A2判定
	float ra, rb;

	ra = a->e.x;
	rb = b->e.x * AbsR[0][0] + b->e.y * AbsR[0][1] + b->e.z * AbsR[0][2];
	if (fabsf(t.x) > ra + rb)return 0;

	ra = a->e.y;
	rb = b->e.x * AbsR[1][0] + b->e.y * AbsR[1][1] + b->e.z * AbsR[1][2];
	if (fabsf(t.y) > ra + rb)return 0;

	ra = a->e.z;
	rb = b->e.x * AbsR[2][0] + b->e.y * AbsR[2][1] + b->e.z * AbsR[2][2];
	if (fabsf(t.z) > ra + rb)return 0;

	//軸L=B0, L=B1, L=B2判定
	ra = a->e.x * AbsR[0][0] + a->e.y * AbsR[1][0] + a->e.z * AbsR[2][0];
	rb = b->e.x;
	if (fabsf(t.x * R[0][0] + t.y * R[1][0] + t.z * R[2][0]) > ra + rb)return 0;

	ra = a->e.x * AbsR[0][1] + a->e.y * AbsR[1][1] + a->e.z * AbsR[2][1];
	rb = b->e.y;
	if (fabsf(t.x * R[0][1] + t.y * R[1][1] + t.z * R[2][1]) > ra + rb)return 0;

	ra = a->e.x * AbsR[0][2] + a->e.y * AbsR[1][2] + a->e.z * AbsR[2][2];
	rb = b->e.y;
	if (fabsf(t.x * R[0][2] + t.y * R[1][2] + t.z * R[2][2]) > ra + rb)return 0;




	//軸L=A0 X B0判定
	ra = a->e.y * AbsR[2][0] + a->e.z * AbsR[1][0];
	rb = b->e.y * AbsR[0][2] + b->e.z * AbsR[0][1];
	if (fabsf(t.z * R[1][0] - t.y * R[2][0]) > ra + rb)return 0;

	//軸L=A0 X B1判定
	ra = a->e.y * AbsR[2][1] + a->e.z * AbsR[1][1];
	rb = b->e.x * AbsR[0][2] + b->e.z * AbsR[0][0];
	if (fabsf(t.z * R[1][1] - t.y * R[2][1]) > ra + rb)return 0;

	//軸L=A0 X B2判定
	ra = a->e.y * AbsR[2][2] + a->e.z * AbsR[1][2];
	rb = b->e.x * AbsR[0][1] + b->e.y * AbsR[0][0];
	if (fabsf(t.z * R[1][2] - t.y * R[2][2]) > ra + rb)return 0;

	//軸L=A1 X B0判定
	ra = a->e.x * AbsR[2][0] + a->e.z * AbsR[0][0];
	rb = b->e.y * AbsR[1][2] + b->e.z * AbsR[1][1];
	if (fabsf(t.x * R[2][0] - t.z * R[0][0]) > ra + rb)return 0;

	//軸L=A1 X B1判定
	ra = a->e.z * AbsR[2][1] + a->e.z * AbsR[0][1];
	rb = b->e.z * AbsR[1][2] + b->e.z * AbsR[1][0];
	if (fabsf(t.x * R[2][1] - t.z * R[0][1]) > ra + rb)return 0;

	//軸L=A1 X B2判定
	ra = a->e.x * AbsR[2][2] + a->e.z * AbsR[0][2];
	rb = b->e.x * AbsR[1][1] + b->e.y * AbsR[1][0];
	if (fabsf(t.x * R[2][2] - t.z * R[0][2]) > ra + rb)return 0;

	//軸L=A2 X B0判定
	ra = a->e.x * AbsR[1][0] + a->e.y * AbsR[0][0];
	rb = b->e.y * AbsR[2][2] + b->e.z * AbsR[2][1];
	if (fabsf(t.y * R[0][0] - t.x * R[1][0]) > ra + rb)return 0;

	//軸L=A2 X B1判定
	ra = a->e.x * AbsR[1][1] + a->e.y * AbsR[0][1];
	rb = b->e.x * AbsR[2][2] + b->e.z * AbsR[2][0];
	if (fabsf(t.y * R[0][1] - t.y * R[1][1]) > ra + rb)return 0;

	//軸L=A2 X B2判定
	ra = a->e.x * AbsR[1][2] + a->e.y * AbsR[0][2];
	rb = b->e.x * AbsR[2][1] + b->e.y * AbsR[2][0];
	if (fabsf(t.y * R[0][2] - t.x * R[1][2]) > ra + rb)return 0;

	return 1;
}

#pragma endregion

