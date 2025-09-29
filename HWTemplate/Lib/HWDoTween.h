#pragma once
#include "HandlerWaltan.h"

/**
* @author   NZ
* @date     25/02/19
* @note		自作Dotweenの定義
*/

/**
 * @class	Dotween
 * @brief	自作Dotween
 */
class HWDotween
{
	friend class HandlerWaltan;

	//
	// クラス
	//

public:

	/**
	 * @class	Dotween
	 * @brief	自作Dotween
	 */
	class TweenEvent
	{
		friend class HWDotween;
	private:
		//! 完了時のコールバック
		std::function<void(TweenEvent*,int)> function;
		//! 経過時間
		int elapsedTime = 0;
		//! 完了までのフレーム
		int duration;
		//! アニメーションさせるTransform
		HWTransform* transform;
		//! アニメーションさせるVECTOR
		VECTOR* animPtr;
		//! アニメーション前のVECTOR
		VECTOR prev;
		//! 目標のVECTOR
		VECTOR target;
	public:
		// ステータス
		bool complete = false;
		// キャンセル用のフラグ
		bool isCancel = false;

	public:
		TweenEvent() {};

		void Subscribe_Move(std::function<void(TweenEvent*, int)> _function, HWTransform* _transform, const VECTOR& _target, int _duration)
		{
			function = _function;
			duration = _duration;
			transform = _transform;
			target = _target;
			prev = _transform->position;
		}
		
		void Subscribe_Rot(std::function<void(TweenEvent*, int)> _function, HWTransform* _transform, const VECTOR& _target, int _duration)
		{
			function = _function;
			duration = _duration;
			transform = _transform;
			target = _target;
			prev = _transform->rotate;
		}

		void Subscribe_Scale(std::function<void(TweenEvent*, int)> _function, HWTransform* _transform, const VECTOR& _target, int _duration)
		{
			function = _function;
			duration = _duration;
			transform = _transform;
			target = _target;
			prev = _transform->scale;
		}

		void Subscribe_Action(std::function<void(TweenEvent*, int)> _function, VECTOR* _scalePtr, const VECTOR& _target, int _duration)
		{
			function = _function;
			duration = _duration;
			animPtr = _scalePtr;
			target = _target;
			prev = *_scalePtr;
		}

		void Subscribe_Delay(std::function<void(TweenEvent*, int)> _function, int _duration)
		{
			function = _function;
			duration = _duration;
		}

		void Execute()
		{
			function(this, elapsedTime++);
		}
	};

	/**
	 * @class	Dotween
	 * @brief	自作Dotween
	 */
	class TweenCallback
	{
		friend class HWDotween;

	public:
		// 紐づいているTweenEvent
		TweenEvent* tweenEvent = nullptr;

	private:
		// 完了時のコールバック
		std::function<void()> onComplete;

	public:
		TweenCallback() {};

		void OnComplete(std::function<void()> _onComplete)
		{
			onComplete = _onComplete;
		}
	};


	//
	// メンバ変数
	//

private:

	//! 登録されたDotween
	static std::unordered_map<TweenEvent*, TweenCallback*> tweens;


	//
	// メソッド
	//

private:

	/**
	 * @brief		更新処理
	 */
	static void Update();

public:

	/**
	 * @brief		オブジェクトを移動させる
	 * @param[in]	移動させるオブジェクト
	 * @param[in]	移動先の座標
	 * @param[in]	移動にかける時間(フレーム)
	 * @return		TweenEventのヘルパークラス
	 */
	static TweenCallback* DoMove(HWTransform* _transform, const VECTOR& _targetPos, int _duration);

	/**
	 * @brief		オブジェクトを回転させる
	 * @param[in]	回転させるオブジェクト
	 * @param[in]	回転先の座標
	 * @param[in]	回転にかける時間(フレーム)
	 * @return		TweenEventのヘルパークラス
	 */
	static TweenCallback* DoRotate(HWTransform* _transform, const VECTOR& _targetRot, int _duration);

	/**
	 * @brief		オブジェクトを拡縮させる
	 * @param[in]	拡縮させるオブジェクト
	 * @param[in]	拡縮先の座標
	 * @param[in]	拡縮にかける時間(フレーム)
	 * @return		TweenEventのヘルパークラス
	 */
	static TweenCallback* DoScale(HWTransform* _transform, const VECTOR& _targetScale, int _duration);

	/**
	 * @brief		オブジェクトを拡縮させる
	 * @param[in]	拡縮させるVEVTOR変数
	 * @param[in]	拡縮先の座標
	 * @param[in]	拡縮にかける時間(フレーム)
	 * @return		TweenEventのヘルパークラス
	 */
	static TweenCallback* DoAction(VECTOR* _scalePtr, const VECTOR& _targetScale, int _duration);

	/**
	 * @brief		一定時間待機
	 * @param[in]	移動にかかる時間(フレーム)
	 * @return		TweenEventのヘルパークラス
	 */
	static TweenCallback* DoDelay(int _duration);
};