#pragma once
#include "../Lib/HWSceneBase.h"


class SceneA : public HWSceneBase
{
public:
	void OnEnter() override
	{
	}
};


REGISTER_SCENE("Scene_A", SceneA)

