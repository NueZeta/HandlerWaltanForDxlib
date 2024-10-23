#include "h/HWAnimator.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		HWAnimatorの実装ファイル
*/


#pragma region privateメソッド


void HWAnimator::AnimPlay()
{
	if (isStop)return;

	// アニメーション1の処理
	if (playIndex1 != -1)
	{
		// 再生時間を進める
		playTime += animInfoVec[playIndex1]->playSpeed;

		// コールバック関数が登録されている場合は再生時間に応じて呼び出す
		auto& callBacks = animInfoVec[playIndex1]->GetCallBack();
		if (!callBacks.empty() && callBacks.find(playTime) != callBacks.end())
			callBacks[playTime]();

		// アニメーションの再生が終了した
		if (playTime >= animInfoVec[playIndex1]->totalTime)
		{
			// 再生時間が総時間を超過している且つ、アニメーションのループフラグが立っているなら
			// アニメーションをループさせる
			if (animInfoVec[playIndex1]->isLoop)
				playTime = fmod(playTime, animInfoVec[playIndex1]->totalTime);
			// ルール再生のアニメーションではない場合、デフォルトアニメーションに戻す
			else
				AnimChange(defaultAnimId);
		}
	}

	// アニメーション1の処理
	if (playIndex2 != -1)
	{
		// アニメーション1のブレンド率を設定
		MV1SetAttachAnimBlendRate(modelHandle,
			animInfoVec[playIndex1]->attachIndex, 1.0f - animBlendRate);

		// アニメーション2のブレンド率を設定
		MV1SetAttachAnimBlendRate(modelHandle,
			animInfoVec[playIndex2]->attachIndex, animBlendRate);

		// ブレンド率が1未満の場合は1に近づける
		if (animBlendRate < 1.0f)
		{
			animBlendRate += blendSpeed;
			// ブレンド率が1以上の場合、アニメーション1を削除し、
			// アニメーション2の情報をアニメーション1に渡す
			if (animBlendRate >= 1.0f)
			{
				MV1DetachAnim(modelHandle, animInfoVec[playIndex1]->attachIndex);
				playIndex1 = playIndex2;
				playIndex2 = -1;
				playTime = 0.0;
			}
		}
	}

	// 変更した再生時間をモデルに反映させる
	if (playIndex1 != -1 && playIndex2 == -1)
		MV1SetAttachAnimTime(modelHandle,
			animInfoVec[playIndex1]->attachIndex, (float)playTime);
}


#pragma endregion

#pragma region publicメソッド


HWAnimator::~HWAnimator()
{
	for (auto it = animInfoVec.begin(); it != animInfoVec.end(); ++it)
		MV1DeleteModel((*it)->animHandle);
}

AnimInfo* HWAnimator::AnimLoad(const std::string& _filePath, const int _animId)
{
	//! アニメーション情報をまとめたクラスのインスタンスを生成
	std::unique_ptr<AnimInfo> animInfo = std::make_unique<AnimInfo>();

	// 初期化処理を行う
	animInfo->filePath = _filePath;
	animInfo->animHandle = MV1LoadModel(_filePath.c_str());

	// モデルロード失敗時の例外error
	if (animInfo->animHandle == -1)
		throw std::runtime_error("Failed to load model: " + animInfo->filePath);

	animInfo->modelHandle = modelHandle;
	animInfo->interruption = true;
	animInfo->isLoop = false;
	animInfo->playSpeed = 1.0f;
	animInfo->totalTime = MV1GetAnimTotalTime(animInfo->animHandle, _animId);
	animInfo->animIndex = _animId;

	// 所有権をvectorに移す
	animInfoVec.push_back(std::move(animInfo));

	return animInfoVec.back().get();
}

void HWAnimator::AnimChange(const int _animId)
{
	// 指示の来たアニメーション番号が無効な場合は変更指示を無視
	if (_animId >= animInfoVec.size() || _animId < 0) return;

	// 再生アニメーションIDが初期値だった場合は
	// パラメータを参照せずに指示の来たアニメーションをセット
	if (playIndex1 == -1 && playIndex2 == -1)
	{
		// 新しいアニメーションをアタッチ
		animInfoVec[_animId]->attachIndex = MV1AttachAnim(modelHandle,
			animInfoVec[_animId]->animIndex, animInfoVec[_animId]->animHandle);

		// 再生時間を初期化
		playTime = 0.0f;
		// 再生アニメーションとして保存
		playIndex1 = _animId;

		return;
	}

	// 再生中のアニメーションが再生中且つ、中断不可の場合は変更指示を無視
	if (playTime < animInfoVec[playIndex1]->totalTime &&
		!animInfoVec[playIndex1]->interruption) return;


	// モーションブレンド中ではない
	else if (playIndex1 != -1 && playIndex2 == -1)
	{
		// 再生アニメーションと同じアニメーションへの変更指示も無視
		if (_animId == playIndex1) return;

		// 新しいアニメーションをアタッチ
		animInfoVec[_animId]->attachIndex = MV1AttachAnim(modelHandle,
			animInfoVec[_animId]->animIndex, animInfoVec[_animId]->animHandle);

		// ブレンド中のアニメーションとして保存
		playIndex2 = _animId;
		// ブレンド率を設定
		animBlendRate = 0.0f;
	}

	else if (playIndex1 != -1 && playIndex2 != -1)
	{
		// ブレンド中のアニメーションと同じアニメーションへの変更指示も無視
		if (_animId == playIndex2) return;
		// ブレンド中のアニメーションが再生中且つ、中断不可の場合は変更指示を無視
		if (playTime < animInfoVec[playIndex2]->totalTime &&
			!animInfoVec[playIndex2]->interruption) return;


		// 現在のアニメーション1をデタッチ
		MV1DetachAnim(modelHandle, animInfoVec[playIndex1]->attachIndex);

		// 現在のアニメーション2をアニメーション1に移動
		playIndex1 = playIndex2;

		// 新しいアニメーションをアタッチ
		animInfoVec[_animId]->attachIndex = MV1AttachAnim(modelHandle,
			animInfoVec[_animId]->animIndex, animInfoVec[_animId]->animHandle);

		// 新しいアニメーションをアニメーション2として設定
		playIndex2 = _animId;

		// ブレンド率をリセット
		animBlendRate = 0.0f;
	}
}


#pragma endregion

#pragma region protectedメソッド




#pragma endregion

#pragma region オーバーライドメソッド


void HWAnimator::Awake()
{
	// 初期値を入れておく
	playTime = 0.0f;
	playIndex1 = -1;
	playIndex2 = -1;
	isStop = false;

	// モデルロード失敗時の例外error
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



