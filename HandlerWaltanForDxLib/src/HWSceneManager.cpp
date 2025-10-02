#include "h/HWSceneManager.h"


HWSceneBase* HWSceneManager::crrScene = nullptr;
HWSceneBase* HWSceneManager::loadScene = nullptr;
std::atomic<LoadParameter> HWSceneManager::loadParam = LoadParameter::None;
std::thread HWSceneManager::loadThread;
std::mutex HWSceneManager::loadMutex;


std::unordered_map<std::string, std::function<HWSceneBase*()>>& HWSceneManager::GetRegistry()
{
    //! シーンクラスの登録(名前 : クラスをインスタンス化するコールバック関数)
    static std::unordered_map<std::string, std::function<HWSceneBase* ()>> registry;
    return registry;
}

void HWSceneManager::RegisterScene(const std::string& name, std::function<HWSceneBase*()> factory)
{
	GetRegistry()[name] = factory;
}

void HWSceneManager::Update()
{
	// 非同期ロードが完了しているか確認
	if (loadParam.load() == LoadParameter::complete)
	{
		// スレッドの終了を待つ
		if (loadThread.joinable())
			loadThread.join();

		// loadSceneのアクセスに排他制御
		std::lock_guard<std::mutex> lock(loadMutex);
		// 実行中のシーンのインスタンスとロードしたシーンのインスタンスを交換
		std::swap(crrScene, loadScene);
		// 遷移前のシーンのインスタンスを削除
		delete loadScene;
		loadScene = nullptr;
		crrScene->OnLoadComplete();
		// ロードパラメータを待機中に更新
		loadParam.store(LoadParameter::None);
	}

	// 実行中のシーンが存在する場合、更新
	if (crrScene)
	{
		crrScene->OnUpdate();
	}
}

HWSceneBase* HWSceneManager::SceneChangeSync(const std::string& name)
{
	// ロードパラメータが待機中でない場合はそのまま終了
	if (loadParam.load() != LoadParameter::None)
		return nullptr;

	// シーンが存在するか調べる
    auto it = GetRegistry().find(name);

	// 存在する場合、インスタンス生成のコールバックを実行
    if (it != GetRegistry().end())
    {
		crrScene = it->second();
		crrScene->OnEnter();
        return crrScene;
    }

    // 存在しない場合、そのまま終了
    return nullptr;
}

void HWSceneManager::SceneChangeAsync(const std::string& name)
{
	// ロードパラメータが待機中でない場合、
	if (loadParam.load() != LoadParameter::None)
		return;

	// シーンが存在するか調べる
	auto it = GetRegistry().find(name);

	// 存在しない場合、そのまま終了
	if (it == GetRegistry().end())
		return;

	//
	// ここまできたら、シーンロード確定
	//

	// ロードパラメータをロード中に更新
	loadParam.store(LoadParameter::Loading);

	//! ロード用のスレッドに値渡しするためのコピー
	std::string sceneName = name;

	// シーンが存在する場合、ロード用のスレッドを作成し、
	// 非同期でシーンをロードする 
	loadThread = std::thread([sceneName]()
		{
			// loadSceneのアクセスに排他制御
			std::lock_guard<std::mutex> lock(loadMutex);
			// シーンのインスタンスを生成
			loadScene = GetRegistry().find(sceneName)->second();
			loadScene->OnEnter();
			// ロードパラメータを完了に更新
			loadParam.store(LoadParameter::complete);
		});
}
