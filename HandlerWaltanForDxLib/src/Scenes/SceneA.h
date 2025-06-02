#pragma once
#include "../Lib/HWSceneBase.h"


class SceneA : public HWSceneBase
{
public:
	void OnEnter() override
	{
		int a = 0;
	}
};


REGISTER_SCENE("Scene_A", SceneA)

