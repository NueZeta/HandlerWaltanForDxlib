#include "h/HWAnimator.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		HWAnimator�̎����t�@�C��
*/


#pragma region private���\�b�h


void HWAnimator::AnimPlay()
{
	if (isStop)return;

	// �A�j���[�V����1�̏���
	if (playIndex1 != -1)
	{
		// �Đ����Ԃ�i�߂�
		playTime += animInfoVec[playIndex1]->playSpeed;

		// �R�[���o�b�N�֐����o�^����Ă���ꍇ�͍Đ����Ԃɉ����ČĂяo��
		auto& callBacks = animInfoVec[playIndex1]->GetCallBack();
		if (!callBacks.empty() && callBacks.find(playTime) != callBacks.end())
			callBacks[playTime]();

		// �A�j���[�V�����̍Đ����I������
		if (playTime >= animInfoVec[playIndex1]->totalTime)
		{
			// �Đ����Ԃ������Ԃ𒴉߂��Ă��銎�A�A�j���[�V�����̃��[�v�t���O�������Ă���Ȃ�
			// �A�j���[�V���������[�v������
			if (animInfoVec[playIndex1]->isLoop)
				playTime = fmod(playTime, animInfoVec[playIndex1]->totalTime);
			// ���[���Đ��̃A�j���[�V�����ł͂Ȃ��ꍇ�A�f�t�H���g�A�j���[�V�����ɖ߂�
			else
				AnimChange(defaultAnimId);
		}
	}

	// �A�j���[�V����1�̏���
	if (playIndex2 != -1)
	{
		// �A�j���[�V����1�̃u�����h����ݒ�
		MV1SetAttachAnimBlendRate(modelHandle,
			animInfoVec[playIndex1]->attachIndex, 1.0f - animBlendRate);

		// �A�j���[�V����2�̃u�����h����ݒ�
		MV1SetAttachAnimBlendRate(modelHandle,
			animInfoVec[playIndex2]->attachIndex, animBlendRate);

		// �u�����h����1�����̏ꍇ��1�ɋ߂Â���
		if (animBlendRate < 1.0f)
		{
			animBlendRate += blendSpeed;
			// �u�����h����1�ȏ�̏ꍇ�A�A�j���[�V����1���폜���A
			// �A�j���[�V����2�̏����A�j���[�V����1�ɓn��
			if (animBlendRate >= 1.0f)
			{
				MV1DetachAnim(modelHandle, animInfoVec[playIndex1]->attachIndex);
				playIndex1 = playIndex2;
				playIndex2 = -1;
				playTime = 0.0;
			}
		}
	}

	// �ύX�����Đ����Ԃ����f���ɔ��f������
	if (playIndex1 != -1 && playIndex2 == -1)
		MV1SetAttachAnimTime(modelHandle,
			animInfoVec[playIndex1]->attachIndex, (float)playTime);
}


#pragma endregion

#pragma region public���\�b�h


HWAnimator::~HWAnimator()
{
	for (auto it = animInfoVec.begin(); it != animInfoVec.end(); ++it)
		MV1DeleteModel((*it)->animHandle);
}

AnimInfo* HWAnimator::AnimLoad(const std::string& _filePath, const int _animId)
{
	//! �A�j���[�V���������܂Ƃ߂��N���X�̃C���X�^���X�𐶐�
	std::unique_ptr<AnimInfo> animInfo = std::make_unique<AnimInfo>();

	// �������������s��
	animInfo->filePath = _filePath;
	animInfo->animHandle = MV1LoadModel(_filePath.c_str());

	// ���f�����[�h���s���̗�Oerror
	if (animInfo->animHandle == -1)
		throw std::runtime_error("Failed to load model: " + animInfo->filePath);

	animInfo->modelHandle = modelHandle;
	animInfo->interruption = true;
	animInfo->isLoop = false;
	animInfo->playSpeed = 1.0f;
	animInfo->totalTime = MV1GetAnimTotalTime(animInfo->animHandle, _animId);
	animInfo->animIndex = _animId;

	// ���L����vector�Ɉڂ�
	animInfoVec.push_back(std::move(animInfo));

	return animInfoVec.back().get();
}

void HWAnimator::AnimChange(const int _animId)
{
	// �w���̗����A�j���[�V�����ԍ��������ȏꍇ�͕ύX�w���𖳎�
	if (_animId >= animInfoVec.size() || _animId < 0) return;

	// �Đ��A�j���[�V����ID�������l�������ꍇ��
	// �p�����[�^���Q�Ƃ����Ɏw���̗����A�j���[�V�������Z�b�g
	if (playIndex1 == -1 && playIndex2 == -1)
	{
		// �V�����A�j���[�V�������A�^�b�`
		animInfoVec[_animId]->attachIndex = MV1AttachAnim(modelHandle,
			animInfoVec[_animId]->animIndex, animInfoVec[_animId]->animHandle);

		// �Đ����Ԃ�������
		playTime = 0.0f;
		// �Đ��A�j���[�V�����Ƃ��ĕۑ�
		playIndex1 = _animId;

		return;
	}

	// �Đ����̃A�j���[�V�������Đ������A���f�s�̏ꍇ�͕ύX�w���𖳎�
	if (playTime < animInfoVec[playIndex1]->totalTime &&
		!animInfoVec[playIndex1]->interruption) return;


	// ���[�V�����u�����h���ł͂Ȃ�
	else if (playIndex1 != -1 && playIndex2 == -1)
	{
		// �Đ��A�j���[�V�����Ɠ����A�j���[�V�����ւ̕ύX�w��������
		if (_animId == playIndex1) return;

		// �V�����A�j���[�V�������A�^�b�`
		animInfoVec[_animId]->attachIndex = MV1AttachAnim(modelHandle,
			animInfoVec[_animId]->animIndex, animInfoVec[_animId]->animHandle);

		// �u�����h���̃A�j���[�V�����Ƃ��ĕۑ�
		playIndex2 = _animId;
		// �u�����h����ݒ�
		animBlendRate = 0.0f;
	}

	else if (playIndex1 != -1 && playIndex2 != -1)
	{
		// �u�����h���̃A�j���[�V�����Ɠ����A�j���[�V�����ւ̕ύX�w��������
		if (_animId == playIndex2) return;
		// �u�����h���̃A�j���[�V�������Đ������A���f�s�̏ꍇ�͕ύX�w���𖳎�
		if (playTime < animInfoVec[playIndex2]->totalTime &&
			!animInfoVec[playIndex2]->interruption) return;


		// ���݂̃A�j���[�V����1���f�^�b�`
		MV1DetachAnim(modelHandle, animInfoVec[playIndex1]->attachIndex);

		// ���݂̃A�j���[�V����2���A�j���[�V����1�Ɉړ�
		playIndex1 = playIndex2;

		// �V�����A�j���[�V�������A�^�b�`
		animInfoVec[_animId]->attachIndex = MV1AttachAnim(modelHandle,
			animInfoVec[_animId]->animIndex, animInfoVec[_animId]->animHandle);

		// �V�����A�j���[�V�������A�j���[�V����2�Ƃ��Đݒ�
		playIndex2 = _animId;

		// �u�����h�������Z�b�g
		animBlendRate = 0.0f;
	}
}


#pragma endregion

#pragma region protected���\�b�h




#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


void HWAnimator::Awake()
{
	// �����l�����Ă���
	playTime = 0.0f;
	playIndex1 = -1;
	playIndex2 = -1;
	isStop = false;

	// ���f�����[�h���s���̗�Oerror
	if (gameObject->GetComponent<HWRenderer>() == nullptr)
		throw std::runtime_error("HWRenderer is not attached");

	modelHandle = gameObject->GetComponent<HWRenderer>()->GetModelHandle();

	blendSpeed = PLAYER_ANIM_BLEND_SPEED;
}

void HWAnimator::Update()
{
	AnimPlay();
}


#pragma endregion



