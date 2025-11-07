#include "h/HWCamera.h"


/**
* @author   NZ
* @date     24/09/20
* @note		HWCameraの実装ファイル
*/


#pragma region privateメソッド




#pragma endregion

#pragma region publicメソッド


HWCamera::HWCamera()
{
}


#pragma endregion

#pragma region protectedメソッド




#pragma endregion

#pragma region オーバーライドメソッド


void HWCamera::Awake()
{
	transform->position = VGet(320.0f, 240.0f, 0);
	target = VGet(320.0f, 240.0f, 1.0f);
}

void HWCamera::LateUpdate()
{
	SetCameraPositionAndTarget_UpVecY(transform->position, target);
}


#pragma endregion