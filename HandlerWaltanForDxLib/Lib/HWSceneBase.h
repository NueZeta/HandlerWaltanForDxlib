#pragma once
#include "HWSceneManager.h"


#define REGISTER_SCENE(NAME, TYPE)                                  \
    namespace {                                                     \
        struct TYPE##SceneRegister {                                \
            TYPE##SceneRegister() {                                 \
                HWSceneManager::RegisterScene(NAME, []() -> HWSceneBase* { return new TYPE(); }); \
            }                                                       \
        };                                                          \
        static TYPE##SceneRegister global_##TYPE##SceneRegister;    \
        void ForceLink_##TYPE() {}                                  \
    }


#define DEFINE_PREFAB(name) \
    void register_##name() { \
        /* プレハブ登録の処理 */ \
    }


class HWSceneBase
{
	// メンバ変数

public:


	// メソッド

public:

	virtual ~HWSceneBase() = default;
    /**
     * @brief		ロード完了時に呼ばれる関数(非同期ロードの場合は別スレッドで呼ばれる)
     */
	virtual void OnEnter() {}
	virtual void OnUpdate() {}
    /**
     * @brief		ロード完了時に呼ばれる関数(非同期ロードの場合のみ呼ばれる)
	 * @detail		非同期ロードの場合は、OnEnterが別スレッドで呼ばれるため、メインスレッドで実行したい処理はここに書く
     */
    virtual void OnLoadComplete() {}
};