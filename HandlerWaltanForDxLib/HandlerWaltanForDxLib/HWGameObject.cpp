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

    std::unique_ptr<HWTransform> transform = std::make_unique<HWTransform>();
    transform->gameObject = this;
    transform->Awake();
    hwComponents.push_back(std::move(transform));

    BubbleSort();
}

HWGameObject::HWGameObject(std::string _name) : priority(0), name(_name)
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transform = std::make_unique<HWTransform>();
    transform->gameObject = this;
    transform->Awake();
    hwComponents.push_back(std::move(transform));

    BubbleSort();
}

HWGameObject::HWGameObject(int _priority) : priority(_priority), name("hwObj")
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transform = std::make_unique<HWTransform>();
    transform->gameObject = this;
    transform->Awake();
    hwComponents.push_back(std::move(transform));

    BubbleSort();
}

HWGameObject::HWGameObject(std::string _name, int _priority) : name(_name), priority(_priority)
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transform = std::make_unique<HWTransform>();
    transform->gameObject = this;
    transform->Awake();
    hwComponents.push_back(std::move(transform));

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
        if(component->active)
            component.get()->Update();
    }
}

void HWGameObject::CallAllOnCollisionEnters()
{
    for (auto& component : hwComponents)
    {
        if(component->active)
            component.get()->OnCollisionEnterHandler();
    }
}

void HWGameObject::CallAllOnCollisionStays()
{
    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->OnCollisionStayHandler();
    }
}

void HWGameObject::CallAllOnCollisionExits()
{
    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->OnCollisionExsitHandler();
    }
}


#pragma endregion

#pragma region publicメソッド





#pragma endregion
