#include "h/HWComponent.h"


/**
* @author   NZ
* @date     24/07/29
* @note		HWComponentの実装ファイル
*/


#pragma region privateメソッド




#pragma endregion

#pragma region publicメソッド


void HWComponent::OnCollisionEnterHandler(HWCollider& _collider)
{
	if (OnCollisionEnterCallBack)
		OnCollisionEnterCallBack(_collider);
}

void HWComponent::OnCollisionStayHandler(HWCollider& _collider)
{
	if (OnCollisionStayCallBack)
		OnCollisionStayCallBack(_collider);
}

void HWComponent::OnCollisionExsitHandler(HWCollider& _collider)
{
	if (OnCollisionExitCallBack)
		OnCollisionExitCallBack(_collider);
}

void HWComponent::OnTriggerEnterHandler(HWCollider& _collider)
{
	if (OnTriggerEnterCallBack)
		OnTriggerEnterCallBack(_collider);
}

void HWComponent::OnTriggerStayHandler(HWCollider& _collider)
{
	if (OnTriggerStayCallBack)
		OnTriggerStayCallBack(_collider);
}

void HWComponent::OnTriggerExsitHandler(HWCollider& _collider)
{
	if (OnTriggerExitCallBack)
		OnTriggerExitCallBack(_collider);
}


#pragma endregion

#pragma region protectedメソッド


HWComponent::HWComponent() : isMultiplePossession(true), active(true), priority(0), completedStartMethod(false),
							 gameObject(nullptr), transform(nullptr)
{
	//各コールバック関数にオーバーライドされたメソッドを代入する
	OnCollisionEnterCallBack = std::bind(&HWComponent::OnCollisionEnter, this, std::placeholders::_1);
	OnCollisionStayCallBack = std::bind(&HWComponent::OnCollisionStay, this, std::placeholders::_1);
	OnCollisionExitCallBack = std::bind(&HWComponent::OnCollisionExit, this, std::placeholders::_1);
	OnTriggerEnterCallBack = std::bind(&HWComponent::OnTriggerEnter, this, std::placeholders::_1);
	OnTriggerStayCallBack = std::bind(&HWComponent::OnTriggerStay, this, std::placeholders::_1);
	OnTriggerExitCallBack = std::bind(&HWComponent::OnTriggerExit, this, std::placeholders::_1);
}


#pragma endregion

