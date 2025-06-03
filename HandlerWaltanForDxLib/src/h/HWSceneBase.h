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
	virtual void OnEnter() {}
	virtual void OnUpdate() {}
};