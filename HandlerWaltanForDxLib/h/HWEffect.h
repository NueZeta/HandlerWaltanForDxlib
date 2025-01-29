#pragma once
#include "HandlerWaltanForDxLib.h"



/**
* @author   Suzuki N
* @date     24/09/15
* @note		エフェクトコンポーネントの定義
*/


/**
 * @enum	StopAction
 * @brief	再生終了時のアクション
 */
enum class StopAction
{
	//! 何もしない(0)
	None,
	//! ループする(1)
	Loop,
	//! 削除する(2)
	Destroy,
	//! 非アクティブにする(3)
	Disable,
	//! コールバック関数を呼ぶ(4)
	Callback,
};


/**
 * @class	HWSphereCollider
 * @brief	エフェクトコンポーネント
 */
class HWEffect : public HWComponent
{
private:
	// メンバ変数

	/**
	 * @brief		エフェクトハンドル
	 * @History		24/10/07 作成(Suzuki N)
	 */
	int effectResourceHandle;

	/**
	 * @brief		再生中のエフェクトハンドル
	 * @History		24/10/07 作成(Suzuki N)
	 */
	int playingEffectHandle;

	/**
	 * @brief		再生速度
	 * @History		24/10/07 作成(Suzuki N)
	 */
	float playSpeed;

	/**
	 * @brief		再生中か
	 * @History		24/10/07 作成(Suzuki N)
	 */
	bool isPlay;

	/**
	 * @brief		再生終了時のコールバック関数
	 * @History		24/10/07 作成(Suzuki N)
	 */
	std::function<void()> CallBack;

	struct Color
	{
		unsigned int r, g, b, a;
	};

	/**
	 * @brief		カラー
	 * @History		24/10/07 作成(Suzuki N)
	 */
	Color color;

public:

	/**
	 * @brief		再生終了時のアクション
	 * @History		24/10/07 作成(Suzuki N)
	 */
	StopAction stopAction;


public:
	// メソッド

	// コンストラクタ
	HWEffect(const std::string& _path, const float _size = 1.0f);
	// コピーコンストラクタ
	HWEffect(const int _handle, const float _size = 1.0f);
	// デストラクタ
	~HWEffect();


#pragma region Getter関数

	/**
	 * @brief		再生状況を取得する
	 * @return		bool 再生中か
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	bool IsPlay() { return isPlay; }

	/**
	 * @brief		エフェクトの再生速度を取得する
	 * @return		float 再生速度
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	float GetPlaySpeed()
	{
		return GetSpeedPlayingEffekseer3DEffect(playingEffectHandle);
	}

	/**
	 * @brief		再生中のエフェクトハンドル
	 * @return		int エフェクトハンドル
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	int GetPlayEffectHandle() { return playingEffectHandle; }

#pragma endregion

#pragma region Setter関数

	/**
	 * @brief		エフェクトを再生する
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	void Play();

	/**
	 * @brief		再生を停止する
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	void Stop();

	/**
	 * @brief		エフェクトの再生速度を設定する
	 * @rparam[in]	const float 再生速度
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	void SetPlaySpeed(float _speed)
	{
		SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, _speed);
		_speed = _speed;
	}

	/**
	 * @brief		エフェクト再生終了時に呼ばれるコールバック関数を登録する
	 * @rparam[in]	std::function<void()> 登録するコールバック関数
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	void SetCallBack(std::function<void()> _callBack)
	{
		CallBack = _callBack;
	}

	/**
	 * @brief		エフェクトのカラーを設定する
	 * @rparam[in]	const Color& カラー
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	void SetColor(const int r, const int g, const int b, const int a)
	{
		if(playingEffectHandle != -1)
		{
			SetColorPlayingEffekseer3DEffect(playingEffectHandle, r, g, b, a);
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;			
		}
	}

#pragma endregion



	void Awake()override;
	void Start()override;
	void Update()override;
};

