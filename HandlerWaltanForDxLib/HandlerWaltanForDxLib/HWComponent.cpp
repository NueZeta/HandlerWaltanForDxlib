#include "h/HWComponent.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HWComponentの実装ファイル
*/


#pragma region privateメソッド




#pragma endregion

#pragma region publicメソッド


void HWComponent::OnCollisionEnterHandler()
{
	if (OnCollisionEnterCallBack)
		OnCollisionEnterCallBack();
}

void HWComponent::OnCollisionStayHandler()
{
	if (OnCollisionStayCallBack)
		OnCollisionStayCallBack();
}

void HWComponent::OnCollisionExsitHandler()
{
	if (OnCollisionExitCallBack)
		OnCollisionExitCallBack();
}


#pragma endregion

#pragma region protectedメソッド


HWComponent::HWComponent() : isMultiplePossession(true), active(true)
{
	//各コールバック関数にオーバーライドされたメソッドを代入する
	OnCollisionEnterCallBack = std::bind(&HWComponent::OnCollisionEnter, this);
	OnCollisionStayCallBack = std::bind(&HWComponent::OnCollisionStay, this);
	OnCollisionExitCallBack = std::bind(&HWComponent::OnCollisionExit, this);
}


#pragma endregion

