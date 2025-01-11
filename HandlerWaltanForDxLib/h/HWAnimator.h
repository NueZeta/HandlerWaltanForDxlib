#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"
#include "HWRenderer.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		アニメーション制御コンポーネントの定義
*/


/**
 * @class	AnimInfo
 * @brief	アニメーション情報
 */
class AnimInfo
{
	friend class HWAnimator;

public:

	/*     メンバ変数     */

	/**
	 * @brief		アニメーションをアタッチするモデル
	 * @History		24/09/24 作成(Suzuki N)
	 */
	int modelHandle;

	/**
	 * @brief		アニメーションのハンドル
	 * @History		24/09/24 作成(Suzuki N)
	 */
	int animHandle;

	/**
	 * @brief		animModelの登録したアニメーションのインデックス
	 * @History		24/09/24 作成(Suzuki N)
	 */
	int animIndex;

	/**
	 * @brief		Modelにアタッチした時のインデックス
	 * @History		24/09/24 作成(Suzuki N)
	 */
	int attachIndex;

	/**
	 * @brief		アニメーションファイル
	 * @History		24/09/24 作成(Suzuki N)
	 */
	std::string filePath;

	/**
	 * @brief		ループするか
	 * @History		24/09/24 作成(Suzuki N)
	 */
	bool isLoop;

	/**
	 * @brief		中断可能か
	 * @History		24/09/24 作成(Suzuki N)
	 */
	bool interruption;

	/**
	 * @brief		再生速度
	 * @History		24/09/24 作成(Suzuki N)
	 */
	double playSpeed;

	/**
	 * @brief		総再生時間
	 * @History		24/09/24 作成(Suzuki N)
	 */
	double totalTime;

private:

	/**
	 * @brief		特定の再生時間に達したときに呼ばれるコールバック関数
	 * @History		24/10/12 作成(Suzuki N)
	 */
	std::unordered_map<double, std::function<void()>> callbacks;

	/**
	 * @brief		再生開始時に呼ばれるコールバック関数
	 * @History		24/10/12 作成(Suzuki N)
	 */
	std::function<void()> startPlaybackCallback;

	/**
	 * @brief		再生終了時に呼ばれるコールバック関数
	 * @History		24/10/12 作成(Suzuki N)
	 */
	std::function<void()> endPlaybackCallback;


public:
	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	AnimInfo() : modelHandle(-1), animHandle(-1), animIndex(-1), attachIndex(-1),
		filePath(""), isLoop(false), interruption(true), playSpeed(-1.f), totalTime(-1.f)
	{}

	/**
	 * @brief		特定の再生時間になったときに呼ばれるコールバックを登録する
	 * @param[in]	float コールバック関数を呼び出したい再生時間
	 * @param[in]	std::function<void()> 登録するコールバック関数
	 * @author		Suzuki N
	 * @date		24/10/12
	 */
	void AddCallBack(double _callTime, std::function<void()> _callback)
	{
		callbacks[_callTime] = _callback;
	}

	/**
	 * @brief		特定の再生時間になったときに呼ばれるコールバックを登録する
	 * @param[in]	float コールバック関数を呼び出したい再生時間
	 * @param[in]	std::function<void()> 登録するコールバック関数
	 * @author		Suzuki N
	 * @date		24/10/12
	 */
	void SubscribeStartPlaybackCallBack(std::function<void()> _callback)
	{
		startPlaybackCallback = _callback;
	}

	/**
	 * @brief		特定の再生時間になったときに呼ばれるコールバックを登録する
	 * @param[in]	float コールバック関数を呼び出したい再生時間
	 * @param[in]	std::function<void()> 登録するコールバック関数
	 * @author		Suzuki N
	 * @date		24/10/12
	 */
	void SubscribeEndPlaybackCallBack(std::function<void()> _callback)
	{
		endPlaybackCallback = _callback;
	}

	/**
	 * @brief		登録されているコールバック関数を取得する
	 * @return		std::unordered_map<float, std::function<void()>>& 
	 * @author		Suzuki N
	 * @date		24/10/12
	 */
	std::unordered_map<double, std::function<void()>>& GetCallBack()
	{
		return callbacks;
	}

};


/**
 * @class	HWAnimator
 * @brief	アニメーション制御管理用のコンポーネント
 */
class HWAnimator : public HWComponent
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HWGameObject;

private:

	/*     メンバ変数     */

	/**
	 * @brief		各アニメーション情報
	 * @History		24/09/24 作成(Suzuki N)
	 */
	std::vector<std::unique_ptr<AnimInfo>> animInfoVec;

	/**
	 * @brief		モデルハンドル
	 * @History		24/09/25 作成(Suzuki N)
	 */
	int modelHandle;

	/**
	 * @brief		再生中のアニメーション1インデックス
	 * @History		24/09/24 作成(Suzuki N)
	 */
	int playIndex1;

	/**
	 * @brief		再生中のアニメーション2インデックス
	 * @History		24/09/25 作成(Suzuki N)
	 */
	int playIndex2;

	/**
	 * @brief		playAnimId1 と playAnimId2 のブレンド率
	 * @History		24/09/25 作成(Suzuki N)
	 */
	float animBlendRate;

	/**
	 * @brief		アニメーションの再生が終了したときに再生するIdleのID
	 * @History		24/09/24 作成(Suzuki N)
	 */
	int defaultAnimId = 0;


public:

	/**
	 * @brief		再生を停止
	 * @History		24/09/24 作成(Suzuki N)
	 */
	bool isStop;

	/**
	 * @brief		ブレンドのスピード
	 * @History		24/09/29 作成(Suzuki N)
	 */
	float blendSpeed;

	/**
	 * @brief		アニメーションの現在の再生時間
	 * @History		24/09/24 作成(Suzuki N)
	 */
	double playTime;


public:
	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	HWAnimator(){}

	/**
	 * @brief		デストラクタ
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	~HWAnimator();

	/**
	 * @brief		アニメーションをロードする ※ロードするアニメーションはアニメーションが一つしかついていないこと
	 * @param[in]	const std::string& アニメーションファイルのパス
	 * @param[in]	const int		   読み込むアニメーションID
	 * @return		AnimInfo& アニメーション情報(戻り値からパラメータを操作する)
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	AnimInfo* AnimLoad(const std::string& _filePath, const int _animId = 0);

	/**
	 * @brief		再生するアニメーションを指定
	 * @param[in]	const int 再生するアニメーションID
	 * @param[in]	bool	  強制的に切り替えるか
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	void AnimChange(const int _animId, bool forcedSwitchover = false);

#pragma region Setter関数

	/**
	 * @brief		アニメーションの再生が終了した時に自動再生されるdefaultアニメーション(Idolアニメーションなど)
	 * @param[in]	const int デフォルトのアニメーションID
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	void SetDefaultAnimId(const int _defaultAnimId) { defaultAnimId = _defaultAnimId; }

#pragma endregion

#pragma region Getter関数

	/**
	 * @brief		アニメーション情報を格納しているコンテナを取得する
	 * @return		std::vector<std::unique_ptr<AnimInfo>>&	アニメーション情報を格納しているコンテナ
	 * @author		Suzuki N
	 * @date		24/09/29
	 */
	std::vector<std::unique_ptr<AnimInfo>>& GetAnimInfoVec() { return animInfoVec; }

	/**
	 * @brief		再生中のアニメーション情報を取得する
	 * @return		AnimInfo*	アニメーション情報
	 * @author		Suzuki N
	 * @date		24/09/29
	 */
	AnimInfo* GetPlayAnimInfo() { return animInfoVec[playIndex1].get(); }

	/**
	 * @brief		再生しているアニメーション1のインデックスを取得する
	 * @return		const int 再生中のアニメーションインデックス1
	 * @author		Suzuki N
	 * @date		24/09/30
	 */
	const int GetPlayAnimId() { return playIndex1; };

	/**
	 * @brief		ブレンドしているアニメーション1のインデックスを取得する
	 * @return		const int ブレンド中のアニメーションインデックス1
	 * @author		Suzuki N
	 * @date		24/09/30
	 */
	const int GetBlendAnimId() { return playIndex2; };

#pragma endregion



private:

	/**
	 * @brief		アニメーションを再生する
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	void AnimPlay();



protected:

#pragma region オーバーライドメソッド

	/**
	 * @brief		HWGameObjectにアタッチされた瞬間に働く
	 * @detail		オーバライドメソッド
	 * @author		Suzuki N
	 * @date		24/09/25
	 */
	void Awake()override;

	/**
	 * @brief		毎フレーム呼ばれる
	 * @detail		オーバーライド関数
	 * @author		Suzuki N
	 * @date		24/09/25
	 */
	void Update() override;

#pragma endregion
};

