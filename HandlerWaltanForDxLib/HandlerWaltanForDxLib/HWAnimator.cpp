#include "h/HWAnimator.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		HWAnimatorの実装ファイル
*/


#pragma region privateメソッド


void HWAnimator::AnimPlay()
{
	// 再生するアニメーションが未設定(-1)だった場合はそのまま終了
	if (playAnimId == -1) return;

	// 再生時間を進める
	playTime += animInfoVec[playAnimId]->playSpeed;
	// 再生時間がトータルタイムを超えた場合
	if (playTime > animInfoVec[playAnimId]->totalTime)
	{
		// ループフラグが立っている場合、playTimeを初期化
		if (animInfoVec[playAnimId]->isLoop)
			playTime = 0.0f;
		// ループアニメーションじゃなければデフォルトに設定されているアニメーションを自動再生
		else
			AnimChange(defaultAnimId);
	}

	// アニメーションを再生する
	MV1AttachAnim(animInfoVec[playAnimId]->modelHandle, 0, animInfoVec[playAnimId]->animHandle);
}


#pragma endregion

#pragma region publicメソッド


AnimInfo& HWAnimator::AnimLoad(const std::string& _filePath, const int _animId)
{
	//! アニメーション情報をまとめたクラスのインスタンスを生成
	std::unique_ptr<AnimInfo> animInfo = std::make_unique<AnimInfo>();

	// 初期化処理を行う
	animInfo->filePath = _filePath;
	animInfo->animHandle = MV1LoadModel(_filePath.c_str());
	animInfo->modelHandle = gameObject->GetComponent<HWRenderer>()->GetModelHandle();
	animInfo->interruption = false;
	animInfo->isLoop = false;
	animInfo->playSpeed = 1.0f;
	animInfo->totalTime = MV1GetAttachAnimTotalTime(animInfo->animHandle, _animId);

	// 所有権をvectorに移す
	animInfoVec.push_back(std::move(animInfo));

	return *animInfoVec.back();
}

void HWAnimator::AnimChange(const int _animId)
{
	// 再生アニメーションIDが初期値だった場合は
	// パラメータを参照せずに指示の来たアニメーションをセット
	if (playAnimId == -1)
	{
		// 各パラメータを上書き
		playAnimId = _animId;
		isStop = false;
	}
	// 同じアニメーションを再生はしない
	else if (playAnimId == _animId) return;

	// 中断不可のアニメーション且つ、
	// 再生時間がトータル時間を超過していない場合はそのまま終了
	if (!animInfoVec[playAnimId]->interruption && 
		playTime <= animInfoVec[playAnimId]->totalTime) return;

	// 再生指示が通った
	playAnimId = _animId;
}


#pragma endregion

#pragma region protectedメソッド




#pragma endregion

#pragma region オーバーライドメソッド


void HWAnimator::Awake()
{
	// 初期値を入れておく
	playTime = 0.0f;
	playAnimId = -1;
	isStop = false;
}

void HWAnimator::Update()
{
	AnimPlay();
}


#pragma endregion



