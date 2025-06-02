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
	// エフェクトリソースを削除する
	//DeleteEffekseerEffect(effectResourceHandle);
}

void HWEffect::Play()
{
	if (isPlay || playingEffectHandle != -1) return;

	// エフェクトを再生する。
	playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);
	// 再生位置
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, transform->position.x, transform->position.y, transform->position.z);
	// 回転
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, (float)Deg2Rad(transform->rotate.x),
		(float)Deg2Rad(transform->rotate.y), (float)Deg2Rad(transform->rotate.z));
	// スケール
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, transform->scale.x, transform->scale.y, transform->scale.z);

	// カラーの設定をしていた場合は、再度設定
	if (!(color.r == 0 && color.g == 0 && color.b == 0 && color.a == 0))
		SetColor(color.r, color.g, color.b, color.a);

	isPlay = true;
}

void HWEffect::Stop()
{
	if (!isPlay || playingEffectHandle == -1) return;
	// エフェクトの再生を中止する
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

	// 再生位置
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, transform->position.x, transform->position.y, transform->position.z);
	// 回転
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, (float)Deg2Rad(transform->rotate.x),
		(float)Deg2Rad(transform->rotate.y), (float)Deg2Rad(transform->rotate.z));
	// スケール
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, transform->scale.x, transform->scale.y, transform->scale.z);


	// 再生終了
	if (IsEffekseer3DEffectPlaying(playingEffectHandle))
	{
		isPlay = false;
		playingEffectHandle = -1;

		// 再生終了時のアクション
		switch (stopAction)
		{
		case StopAction::None:
			break;

		case StopAction::Loop:
			// 再度再生
			Play();
			break;

		case StopAction::Destroy:
			// 自身のGameObjectを削除する
			delete(gameObject);
			break;

		case StopAction::Disable:
			// 自身のGameObjectを非アクティブにする
			gameObject->active = false;
			break;

		case StopAction::Callback:
			// 登録されたコールバック関数を呼ぶ
			if (CallBack)
				CallBack();
			break;
		}
	}
}
