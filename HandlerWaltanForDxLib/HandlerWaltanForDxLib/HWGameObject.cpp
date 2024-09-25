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

    std::unique_ptr<HWTransform> transformCp = std::make_unique<HWTransform>();
    transformCp->gameObject = this;
    transformCp->Awake();
    hwComponents.push_back(std::move(transformCp));
    transform = GetComponent<HWTransform>();

    BubbleSort();
}

HWGameObject::HWGameObject(const std::string& _name) : priority(0), name(_name)
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transformCp = std::make_unique<HWTransform>();
    transformCp->gameObject = this;
    transformCp->Awake();
    hwComponents.push_back(std::move(transformCp));
    transform = GetComponent<HWTransform>();

    BubbleSort();
}

HWGameObject::HWGameObject(int _priority) : priority(_priority), name("hwObj")
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transformCp = std::make_unique<HWTransform>();
    transformCp->gameObject = this;
    transformCp->Awake();
    hwComponents.push_back(std::move(transformCp));
    transform = GetComponent<HWTransform>();

    BubbleSort();
}

HWGameObject::HWGameObject(const std::string& _name, int _priority) : name(_name), priority(_priority)
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transformCp = std::make_unique<HWTransform>();
    transformCp->gameObject = this;
    transformCp->Awake();
    hwComponents.push_back(std::move(transformCp));
    transform = GetComponent<HWTransform>();

    BubbleSort();
}

HWGameObject::HWGameObject(const HWGameObject& _object)
{

}


#pragma endregion


HWGameObject::~HWGameObject()
{
    auto it = std::find(gameObjects.begin(), gameObjects.end(), this);
    if (it != gameObjects.end())
        gameObjects.erase(it);
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

void HWGameObject::CallAllOnCollisionEnters(HWCollider& _collider)
{
    for (auto& component : hwComponents)
    {
        if(component->active)
            component.get()->OnCollisionEnterHandler(_collider);
    }
}

void HWGameObject::CallAllOnCollisionStays(HWCollider& _collider)
{
    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->OnCollisionStayHandler(_collider);
    }
}

void HWGameObject::CallAllOnCollisionExits(HWCollider& _collider)
{
    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->OnCollisionExsitHandler(_collider);
    }
}

void HWGameObject::CallAllOnTriggerEnters(HWCollider& _collider)
{
    for (auto& component : hwComponents)
    {
        if(component->active)
            component.get()->OnTriggerEnterHandler(_collider);
    }
}

void HWGameObject::CallAllOnTriggerStays(HWCollider& _collider)
{
    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->OnTriggerStayHandler(_collider);
    }
}

void HWGameObject::CallAllOnTriggerExits(HWCollider& _collider)
{
    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->OnTriggerExsitHandler(_collider);
    }
}


#pragma endregion

#pragma region publicメソッド





#pragma endregion
