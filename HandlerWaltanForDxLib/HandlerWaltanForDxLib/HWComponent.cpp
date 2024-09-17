#include "h/HWComponent.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HWComponentの実装ファイル
*/


#pragma region privateメソッド




#pragma endregion

#pragma region publicメソッド


void HWComponent::OnCollisionEnterHandler(HWCollider* _collider)
{
	if (OnCollisionEnterCallBack)
		OnCollisionEnterCallBack(_collider);
}

void HWComponent::OnCollisionStayHandler(HWCollider* _collider)
{
	if (OnCollisionStayCallBack)
		OnCollisionStayCallBack(_collider);
}

void HWComponent::OnCollisionExsitHandler(HWCollider* _collider)
{
	if (OnCollisionExitCallBack)
		OnCollisionExitCallBack(_collider);
}


#pragma endregion

#pragma region protectedメソッド


HWComponent::HWComponent() : isMultiplePossession(true), active(true)
{
	//各コールバック関数にオーバーライドされたメソッドを代入する
	OnCollisionEnterCallBack = std::bind(&HWComponent::OnCollisionEnter, this, std::placeholders::_1);
	OnCollisionStayCallBack = std::bind(&HWComponent::OnCollisionStay, this, std::placeholders::_1);
	OnCollisionExitCallBack = std::bind(&HWComponent::OnCollisionExit, this, std::placeholders::_1);
}


#pragma endregion

