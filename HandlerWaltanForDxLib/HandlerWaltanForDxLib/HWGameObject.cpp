#include "h/HWGameObject.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HWGameObjectの実装ファイル
*/


// 静的メンバ変数の初期化
std::vector<HWGameObject*> HWGameObject::gameObjects;


#pragma region コンストラクタ


HWGameObject::HWGameObject() : priority(0), name("hwObj")
{
    gameObjects.push_back(this);
    AddComponent(std::make_unique<HWTransform>());
    BubbleSort();
}

HWGameObject::HWGameObject(std::string _name) : priority(0), name(_name)
{
    gameObjects.push_back(this);
    AddComponent(std::make_unique<HWTransform>());
    BubbleSort();
}

HWGameObject::HWGameObject(int _priority) : priority(_priority), name("hwObj")
{
    gameObjects.push_back(this);
    AddComponent(std::make_unique<HWTransform>());
    BubbleSort();
}

HWGameObject::HWGameObject(std::string _name, int _priority) : name(_name), priority(_priority)
{
    gameObjects.push_back(this);
    AddComponent(std::make_unique<HWTransform>());
    BubbleSort();
}


#pragma endregion


HWGameObject::~HWGameObject()
{
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
    {
        if (*it == this)
        {
            gameObjects.erase(it);
            break;
        }
    }
}


#pragma region privateメソッド


void HWGameObject::BubbleSort()
{
    std::sort(gameObjects.begin(), gameObjects.end(), [](HWGameObject* a, HWGameObject* b) {
        return a->priority > b->priority; });
}


void HWGameObject::CallAllUpdates()
{
    for (auto& component : hwComponents)
    {
        component.get()->Update();
    }
}

void HWGameObject::CallAllOnCollisionEnters()
{
    for (auto& component : hwComponents)
    {
        component.get()->OnCollisionEnterHandler();
    }
}

void HWGameObject::CallAllOnCollisionStays()
{
    for (auto& component : hwComponents)
    {
        component.get()->OnCollisionStayHandler();
    }
}

void HWGameObject::CallAllOnCollisionExits()
{
    for (auto& component : hwComponents)
    {
        component.get()->OnCollisionExsitHandler();
    }
}


#pragma endregion

#pragma region publicメソッド


void HWGameObject::AddComponent(std::unique_ptr<HWComponent> _component)
{
    _component->SetGameObject(this);
    //_component->Start();
    hwComponents.push_back(std::move(_component));
}


#pragma endregion
