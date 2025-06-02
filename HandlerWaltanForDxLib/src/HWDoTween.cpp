#include "h/HWDoTween.h"


// 静的メンバ変数の初期化
std::unordered_map<HWDotween::TweenEvent*, HWDotween::TweenCallback*> HWDotween::tweens = {};


void HWDotween::Update()
{
	for (auto it = tweens.begin(); it != tweens.end();)
	{
		// Tweenイベントを実行
		it->first->Execute();

		// Tween完了時のコールバックを呼び出す
		if(it->first->complete)
		{
			if(it->second->onComplete)
				it->second->onComplete();

			//
			// 登録を解除
			//

			delete it->first;
			delete it->second;
			it = tweens.erase(it); // 要素を削除し、イテレータを更新
		}
		else
			++it;
	}
}


HWDotween::TweenCallback* HWDotween::DoMove(HWTransform* _transform, const VECTOR& _targetPos, int _duration)
{
	//! 戻り値
	TweenCallback* tweenCallback = new TweenCallback();
	//! Tweenイベント
	TweenEvent* tweenEvent = new TweenEvent();

	//
	// Tweenの登録
	//

	tweens[tweenEvent] = tweenCallback;
	tweenEvent->Subscribe_Move([&](TweenEvent* _tweenEvent, int _frame)
		{
			float rate = (float)_tweenEvent->elapsedTime / (float)_tweenEvent->duration;
			// 移動処理
			_tweenEvent->transform->position = Lerp(_tweenEvent->prev, _tweenEvent->target, rate);
			// 完了判定
			if (_tweenEvent->elapsedTime >= _tweenEvent->duration)
				_tweenEvent->complete = true;
		}, _transform, _targetPos, _duration);

	return tweenCallback;
}

HWDotween::TweenCallback* HWDotween::DoRotate(HWTransform* _transform, const VECTOR& _targetRot, int _duration)
{
	//! 戻り値
	TweenCallback* tweenCallback = new TweenCallback();
	//! Tweenイベント
	TweenEvent* tweenEvent = new TweenEvent();

	//
	// Tweenの登録
	//

	tweens[tweenEvent] = tweenCallback;
	tweenEvent->Subscribe_Rot([&](TweenEvent* _tweenEvent, int _frame)
		{
			float rate = (float)_tweenEvent->elapsedTime / (float)_tweenEvent->duration;
			// 移動処理
			_tweenEvent->transform->rotate = Lerp(_tweenEvent->prev, _tweenEvent->target, rate);
			// 完了判定
			if (_tweenEvent->elapsedTime >= _tweenEvent->duration)
				_tweenEvent->complete = true;
		}, _transform, _targetRot, _duration);

	return tweenCallback;
}

HWDotween::TweenCallback* HWDotween::DoScale(HWTransform* _transform, const VECTOR& _targetScale, int _duration)
{
	//! 戻り値
	TweenCallback* tweenCallback = new TweenCallback();
	//! Tweenイベント
	TweenEvent* tweenEvent = new TweenEvent();

	//
	// Tweenの登録
	//

	tweens[tweenEvent] = tweenCallback;
	tweenEvent->Subscribe_Scale([&](TweenEvent* _tweenEvent, int _frame)
		{
			float rate = (float)_tweenEvent->elapsedTime / (float)_tweenEvent->duration;
			// 移動処理
			_tweenEvent->transform->scale = Lerp(_tweenEvent->prev, _tweenEvent->target, rate);
			// 完了判定
			if (_tweenEvent->elapsedTime >= _tweenEvent->duration)
				_tweenEvent->complete = true;
		}, _transform, _targetScale, _duration);

	return tweenCallback;
}

HWDotween::TweenCallback* HWDotween::DoDelay(int _duration)
{
	//! 戻り値
	TweenCallback* tweenCallback = new TweenCallback();
	//! Tweenイベント
	TweenEvent* tweenEvent = new TweenEvent();

	//
	// Tweenの登録
	//

	tweens[tweenEvent] = tweenCallback;
	tweenEvent->Subscribe_Delay([&](TweenEvent* _tweenEvent, int _frame)
		{
			if (_tweenEvent->elapsedTime >= _tweenEvent->duration)
				_tweenEvent->complete = true;
		}, _duration);

	return tweenCallback;
}
