#include "h/HWCamera.h"


/**
* @author   Suzuki N
* @date     24/09/20
* @note		HWCamera�̎����t�@�C��
*/


#pragma region private���\�b�h




#pragma endregion

#pragma region public���\�b�h


HWCamera::HWCamera()
{
}


#pragma endregion

#pragma region protected���\�b�h




#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


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