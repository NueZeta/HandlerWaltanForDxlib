#include "h/HWDoTween.h"


// �ÓI�����o�ϐ��̏�����
std::unordered_map<HWDotween::TweenEvent*, HWDotween::TweenCallback*> HWDotween::tweens = {};


void HWDotween::Update()
{
	for (auto it = tweens.begin(); it != tweens.end();)
	{
		// Tween�C�x���g�����s
		it->first->Execute();

		// Tween�̃L�����Z��
		if(it->first->isCancel)
		{
			//
			// �o�^������
			//

			delete it->first;
			delete it->second;
			it = tweens.erase(it); // �v�f���폜���A�C�e���[�^���X�V
		}
		// Tween�������̃R�[���o�b�N���Ăяo��
		else if(it->first->complete)
		{
			if(it->second->onComplete)
				it->second->onComplete();

			//
			// �o�^������
			//

			delete it->first;
			delete it->second;
			it = tweens.erase(it); // �v�f���폜���A�C�e���[�^���X�V
		}
		else
			++it;
	}
}


HWDotween::TweenCallback* HWDotween::DoMove(HWTransform* _transform, const VECTOR& _targetPos, int _duration)
{
	//! �߂�l
	TweenCallback* tweenCallback = new TweenCallback();
	//! Tween�C�x���g
	TweenEvent* tweenEvent = new TweenEvent();

	// �߂�l����R�Â��Ă���TweenEvent���Q�Ƃł���悤�ɂ���
	tweenCallback->tweenEvent = tweenEvent;

	//
	// Tween�̓o�^
	//

	tweens[tweenEvent] = tweenCallback;
	tweenEvent->Subscribe_Move([&](TweenEvent* _tweenEvent, int _frame)
		{
			float rate = (float)_tweenEvent->elapsedTime / (float)_tweenEvent->duration;
			// �ړ�����
			_tweenEvent->transform->position = Lerp(_tweenEvent->prev, _tweenEvent->target, rate);
			// ��������
			if (_tweenEvent->elapsedTime >= _tweenEvent->duration)
				_tweenEvent->complete = true;
		}, _transform, _targetPos, _duration);

	return tweenCallback;
}

HWDotween::TweenCallback* HWDotween::DoRotate(HWTransform* _transform, const VECTOR& _targetRot, int _duration)
{
	//! �߂�l
	TweenCallback* tweenCallback = new TweenCallback();
	//! Tween�C�x���g
	TweenEvent* tweenEvent = new TweenEvent();

	// �߂�l����R�Â��Ă���TweenEvent���Q�Ƃł���悤�ɂ���
	tweenCallback->tweenEvent = tweenEvent;

	//
	// Tween�̓o�^
	//

	tweens[tweenEvent] = tweenCallback;
	tweenEvent->Subscribe_Rot([&](TweenEvent* _tweenEvent, int _frame)
		{
			float rate = (float)_tweenEvent->elapsedTime / (float)_tweenEvent->duration;
			// �ړ�����
			_tweenEvent->transform->rotate = Lerp(_tweenEvent->prev, _tweenEvent->target, rate);
			// ��������
			if (_tweenEvent->elapsedTime >= _tweenEvent->duration)
				_tweenEvent->complete = true;
		}, _transform, _targetRot, _duration);

	return tweenCallback;
}

HWDotween::TweenCallback* HWDotween::DoScale(HWTransform* _transform, const VECTOR& _targetScale, int _duration)
{
	//! �߂�l
	TweenCallback* tweenCallback = new TweenCallback();
	//! Tween�C�x���g
	TweenEvent* tweenEvent = new TweenEvent();

	// �߂�l����R�Â��Ă���TweenEvent���Q�Ƃł���悤�ɂ���
	tweenCallback->tweenEvent = tweenEvent;

	//
	// Tween�̓o�^
	//

	tweens[tweenEvent] = tweenCallback;
	tweenEvent->Subscribe_Scale([&](TweenEvent* _tweenEvent, int _frame)
		{
			float rate = (float)_tweenEvent->elapsedTime / (float)_tweenEvent->duration;
			// �ړ�����
			_tweenEvent->transform->scale = Lerp(_tweenEvent->prev, _tweenEvent->target, rate);
			// ��������
			if (_tweenEvent->elapsedTime >= _tweenEvent->duration)
				_tweenEvent->complete = true;
		}, _transform, _targetScale, _duration);

	return tweenCallback;
}

HWDotween::TweenCallback* HWDotween::DoAction(VECTOR* _posPtr, const VECTOR& _targetPos, int _duration)
{
	//! �߂�l
	TweenCallback* tweenCallback = new TweenCallback();
	//! Tween�C�x���g
	TweenEvent* tweenEvent = new TweenEvent();

	// �߂�l����R�Â��Ă���TweenEvent���Q�Ƃł���悤�ɂ���
	tweenCallback->tweenEvent = tweenEvent;

	//
	// Tween�̓o�^
	//

	tweens[tweenEvent] = tweenCallback;
	tweenEvent->Subscribe_Action([&](TweenEvent* _tweenEvent, int _frame)
		{
			float rate = (float)_tweenEvent->elapsedTime / (float)_tweenEvent->duration;
			// �ړ�����
			*_tweenEvent->animPtr = Lerp(_tweenEvent->prev, _tweenEvent->target, rate);
			// ��������
			if (_tweenEvent->elapsedTime >= _tweenEvent->duration)
				_tweenEvent->complete = true;
		}, _posPtr, _targetPos, _duration);

	return tweenCallback;
}



HWDotween::TweenCallback* HWDotween::DoDelay(int _duration)
{
	//! �߂�l
	TweenCallback* tweenCallback = new TweenCallback();
	//! Tween�C�x���g
	TweenEvent* tweenEvent = new TweenEvent();

	// �߂�l����R�Â��Ă���TweenEvent���Q�Ƃł���悤�ɂ���
	tweenCallback->tweenEvent = tweenEvent;

	//
	// Tween�̓o�^
	//

	tweens[tweenEvent] = tweenCallback;
	tweenEvent->Subscribe_Delay([&](TweenEvent* _tweenEvent, int _frame)
		{
			if (_tweenEvent->elapsedTime >= _tweenEvent->duration)
				_tweenEvent->complete = true;
		}, _duration);

	return tweenCallback;
}
