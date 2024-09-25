#include "h/HWAnimator.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		HWAnimatorの実装ファイル
*/


#pragma region privateメソッド


void HWAnimator::AnimPlay()
{
	// ブレンド率が１以下の場合は１に近づける
	if (animBlendRate < 1.0f)
	{
		animBlendRate += PLAYER_ANIM_BLEND_SPEED * GameTime::DeltaTime();
		if (animBlendRate > 1.0f)
		{
			animBlendRate = 1.0f;
		}
	}

	// 再生しているアニメーション１の処理
	if (playAnimId1 != -1)
	{
		// アニメーションの総時間を取得
		float animTotalTime = animInfoVec[playAnimId1]->totalTime;

		// 再生時間を進める
		playTime1 += animInfoVec[playAnimId1]->playSpeed * GameTime::DeltaTime();

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (playTime1 >= animTotalTime)
		{
			playTime1 = fmodf(playTime1, animTotalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(animInfoVec[playAnimId1]->modelHandle, playAnimId1, playTime1);

		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(animInfoVec[playAnimId1]->modelHandle, playAnimId1, animBlendRate);
	}

	// 再生しているアニメーション２の処理
	if (playAnimId1 != -1)
	{
		// アニメーションの総時間を取得
		float animTotalTime = MV1GetAttachAnimTotalTime(animInfoVec[playAnimId2]->modelHandle, playAnimId2);

		// 再生時間を進める
		playTime2 += animInfoVec[playAnimId2]->playSpeed * GameTime::DeltaTime();

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (playTime2 > animTotalTime)
		{
			playTime2 = fmodf(playTime2, animTotalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(animInfoVec[playAnimId2] ->modelHandle, playAnimId2, playTime2);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(animInfoVec[playAnimId2]->modelHandle , playAnimId2, 1.0f - animBlendRate);
	}
}


#pragma endregion

#pragma region publicメソッド


HWAnimator::~HWAnimator()
{
	for (auto it = animInfoVec.begin(); it != animInfoVec.end(); ++it)
		MV1DeleteModel((*it)->animHandle);
}

AnimInfo& HWAnimator::AnimLoad(const std::string& _filePath, const int _animId)
{
	//! アニメーション情報をまとめたクラスのインスタンスを生成
	std::unique_ptr<AnimInfo> animInfo = std::make_unique<AnimInfo>();

	// 初期化処理を行う
	animInfo->filePath = _filePath;
	animInfo->animHandle = MV1LoadModel(_filePath.c_str());
	animInfo->modelHandle = gameObject->GetComponent<HWRenderer>()->GetModelHandle();
	animInfo->interruption = true;
	animInfo->isLoop = false;
	animInfo->playSpeed = 1.0f;
	animInfo->totalTime = MV1GetAttachAnimTotalTime(animInfo->animHandle, _animId);

	// 所有権をvectorに移す
	animInfoVec.push_back(std::move(animInfo));

	return *animInfoVec.back();
}

void HWAnimator::AnimChange(const int _animId)
{
	// 指示の来たアニメーション番号が登録されているアニメーションの総数を超過している場合
	if (_animId >= animInfoVec.size())
		return;

	// 再生アニメーションIDが初期値だった場合は
	// パラメータを参照せずに指示の来たアニメーションをセット
	if (playAnimId1 == -1)
	{
		// 各パラメータを上書き
		isStop = false;
		playAnimId1 = _animId;
	}

	// 同じアニメーションを再生はしない
	else if (playAnimId1 == _animId) return;

	// 中断不可のアニメーション且つ、
	// 再生時間がトータル時間を超過していない場合はそのまま終了
	if (!animInfoVec[playAnimId1]->interruption && 
		playTime1 <= animInfoVec[playAnimId1]->totalTime) return;

	// 再生指示が通った

	// 再生中のアニメーション2がすでに存在する場合はデタッチする
	if (playAnimId2 != -1)
	{
		MV1DetachAnim(animInfoVec[playAnimId1]->modelHandle, playAnimId2);
		playAnimId2 = -1;
	}
	// アニメーション1の情報を2に移動する
	playAnimId2 = playAnimId1;
	playTime2 = playTime1;

	// 新しいアニメーションをアタッチ
	playAnimId1 = MV1AttachAnim(animInfoVec[_animId]->modelHandle, 0, animInfoVec[_animId]->animHandle);
	playTime1 = 0.0f;

	// ブレンド率は再生中のモーション２が有効ではない場合は１．０ｆ( 再生中のモーション１が１００％の状態 )にする
	animBlendRate = playAnimId2 == -1 ? 1.0f : 0.0f;
}


#pragma endregion

#pragma region protectedメソッド




#pragma endregion

#pragma region オーバーライドメソッド


void HWAnimator::Awake()
{
	// 初期値を入れておく
	playTime1 = 0.0f;
	playAnimId1 = -1;
	isStop = false;
}

void HWAnimator::Update()
{
	AnimPlay();
}


#pragma endregion



