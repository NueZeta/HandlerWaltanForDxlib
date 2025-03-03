#include "h/HWImage.h"

HWImage::HWImage(const std::string& _path, ImageRenderType _renderType)
	: graphHandle(LoadGraph(_path.c_str())), renderType(_renderType), isTrans(false)
{
}

HWImage::~HWImage()
{
	DeleteGraph(graphHandle);
}

void HWImage::LateUpdate()
{
	// ’Êí•`‰æ
	switch (renderType)
	{
	case ImageRenderType::Default:
		DrawGraph(transform->position.x, transform->position.y, graphHandle, isTrans);
		break;
	case ImageRenderType::Custom:
		if(customRenderFunction)
			customRenderFunction();
		break;
	}

}
