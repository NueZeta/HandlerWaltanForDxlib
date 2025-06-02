#include "h/HWEffect.h"

HWEffect::HWEffect(const std::string& _path, const float _size)
	: effectResourceHandle(LoadEffekseerEffect(_path.c_str(), _size)), playingEffectHandle(-1),
	playSpeed(-1), isPlay(false), stopAction(StopAction::None), color{ 0,0,0,0 }
{
}

HWEffect::HWEffect(const int _handle, const float _size)
	: effectResourceHandle(_handle), playingEffectHandle(-1),
	playSpeed(-1), isPlay(false), stopAction(StopAction::None), color{ 0,0,0,0 }
{
}

HWEffect::~HWEffect()
{
	// �G�t�F�N�g���\�[�X���폜����
	//DeleteEffekseerEffect(effectResourceHandle);
}

void HWEffect::Play()
{
	if (isPlay || playingEffectHandle != -1) return;

	// �G�t�F�N�g���Đ�����B
	playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);
	// �Đ��ʒu
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, transform->position.x, transform->position.y, transform->position.z);
	// ��]
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, (float)Deg2Rad(transform->rotate.x),
		(float)Deg2Rad(transform->rotate.y), (float)Deg2Rad(transform->rotate.z));
	// �X�P�[��
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, transform->scale.x, transform->scale.y, transform->scale.z);

	// �J���[�̐ݒ�����Ă����ꍇ�́A�ēx�ݒ�
	if (!(color.r == 0 && color.g == 0 && color.b == 0 && color.a == 0))
		SetColor(color.r, color.g, color.b, color.a);

	isPlay = true;
}

void HWEffect::Stop()
{
	if (!isPlay || playingEffectHandle == -1) return;
	// �G�t�F�N�g�̍Đ��𒆎~����
	StopEffekseer3DEffect(playingEffectHandle);
	playingEffectHandle = -1;
	isPlay = false;
}

void HWEffect::Awake()
{
}

void HWEffect::Start()
{
}

void HWEffect::Update()
{
	if (!isPlay) return;

	// �Đ��ʒu
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, transform->position.x, transform->position.y, transform->position.z);
	// ��]
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, (float)Deg2Rad(transform->rotate.x),
		(float)Deg2Rad(transform->rotate.y), (float)Deg2Rad(transform->rotate.z));
	// �X�P�[��
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, transform->scale.x, transform->scale.y, transform->scale.z);


	// �Đ��I��
	if (IsEffekseer3DEffectPlaying(playingEffectHandle))
	{
		isPlay = false;
		playingEffectHandle = -1;

		// �Đ��I�����̃A�N�V����
		switch (stopAction)
		{
		case StopAction::None:
			break;

		case StopAction::Loop:
			// �ēx�Đ�
			Play();
			break;

		case StopAction::Destroy:
			// ���g��GameObject���폜����
			delete(gameObject);
			break;

		case StopAction::Disable:
			// ���g��GameObject���A�N�e�B�u�ɂ���
			gameObject->active = false;
			break;

		case StopAction::Callback:
			// �o�^���ꂽ�R�[���o�b�N�֐����Ă�
			if (CallBack)
				CallBack();
			break;
		}
	}
}
