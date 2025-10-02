#pragma once
#include "HWSceneBase.h"
#include <unordered_map>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>


enum class LoadParameter
{
	// 待機中
	None,
	// 読み込み中
	Loading,
	// 読み込み完了
	complete,
};


class HWSceneManager
{
	// メンバ変数

private:

	//! 実行中のシーン
	static HWSceneBase* crrScene;
	//! 非同期で読み込んだシーンのインスタンス
	static HWSceneBase* loadScene;
	//! シーンロード用のスレッド
	static std::thread loadThread;

public:

	//! シーンロードのパラメータ
	static std::atomic<LoadParameter> loadParam;
	//! ロード中のスレッドセーフ変数
	static std::mutex loadMutex;


	// メソッド

private:

	/**
	 * @brief		登録されているシーンオブジェクトを取得する
	 * @return		登録されているシーンオブジェクト
	 */
	static std::unordered_map <std::string, std::function<HWSceneBase*()>>& GetRegistry();

public:

	/**
	 * @brief		シーンオブジェクトを登録する
	 * @detail		マクロによって登録されるため、手動で呼ぶ必要はない
	 * @param[in]	シーン名 : シーンをインスタンス化するコールバック関数
	 */
	static void RegisterScene(const std::string& name, std::function<HWSceneBase*()> factory);

	/**
	 * @brief		更新処理
	 */
	static void Update();

	/**
	 * @brief		シーンを変更する(同期読み込み)
	 * @param[in]	遷移先のシーン名
	 * @return		遷移後のシーンオブジェクトのインスタンス
	 */
	static HWSceneBase* SceneChangeSync(const std::string& name);

	/**
	 * @brief		シーンを変更する(非同期読み込み)
	 * @param[in]	遷移先のシーン名
	 */
	static void SceneChangeAsync(const std::string& name);
};