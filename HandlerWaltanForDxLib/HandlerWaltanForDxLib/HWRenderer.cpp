#include "h/HWRenderer.h"


/**
* @author   Suzuki N
* @date     24/08/25
* @note		HWRenderer�̎����t�@�C��
*/


#pragma region �R���X�g���N�^


HWRenderer::HWRenderer(const int _modelHandle)
{
	priority = -20;

	// �����̃��f���n���h�����畡���������f�����g��
	modelHandle = MV1DuplicateModel(_modelHandle);
}

HWRenderer::HWRenderer(const std::string& _pass)
{
	modelHandle = MV1LoadModel(_pass.c_str());
	priority = -20;
}

HWRenderer::~HWRenderer()
{
	MV1DeleteModel(modelHandle);
}


#pragma endregion

#pragma region private���\�b�h




#pragma endregion

#pragma region public���\�b�h





#pragma endregion


#pragma region �I�[�o�[���C�h���\�b�h


void HWRenderer::Start()
{
	if (gameObject->name == "Map" || gameObject->name == "map" ||
		gameObject->name == "Stage" || gameObject->name == "stage")
	{
		// ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
		MV1SetupCollInfo(modelHandle, -1);
	}
}

void HWRenderer::LateUpdate()
{
	if (modelHandle == -1)
	{
		return;
	}

	// HWTransform�̃O���[�o���ϊ��s����Q�Ƃ��ă��f���ɓK�p
	MV1SetMatrix(modelHandle, transform->globalMat);
	// ���f����`��
	MV1DrawModel(modelHandle);
}


#pragma endregion
