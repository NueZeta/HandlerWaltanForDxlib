#include "h/HWGameObject.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HWGameObjectの実装ファイル
*/


// 静的メンバ変数の初期化
std::vector<HWGameObject*> HWGameObject::gameObjects;


#pragma region コンストラクタ


HWGameObject::HWGameObject() : priority(0), name("hwObj"), parent(nullptr), active(true)
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transformCp = std::make_unique<HWTransform>();
    transformCp->gameObject = this;
    transformCp->Awake();
    hwComponents.push_back(std::move(transformCp));
    transform = GetComponent<HWTransform>();

    BubbleSort();
}

HWGameObject::HWGameObject(const std::string& _name) : priority(0), name(_name), parent(nullptr),
                           active(true)
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transformCp = std::make_unique<HWTransform>();
    transformCp->gameObject = this;
    transformCp->Awake();
    hwComponents.push_back(std::move(transformCp));
    transform = GetComponent<HWTransform>();

    BubbleSort();
}

HWGameObject::HWGameObject(int _priority) : priority(_priority), name("hwObj"), parent(nullptr), 
                           active(true)
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transformCp = std::make_unique<HWTransform>();
    transformCp->gameObject = this;
    transformCp->Awake();
    hwComponents.push_back(std::move(transformCp));
    transform = GetComponent<HWTransform>();

    BubbleSort();
}

HWGameObject::HWGameObject(const std::string& _name, int _priority) : name(_name), priority(_priority), 
                           parent(nullptr), active(true)
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transformCp = std::make_unique<HWTransform>();
    transformCp->gameObject = this;
    transformCp->Awake();
    hwComponents.push_back(std::move(transformCp));
    transform = GetComponent<HWTransform>();

    BubbleSort();
}

HWGameObject::HWGameObject(const HWGameObject& _other, const CopyType copyType) : name(_other.name),
                           priority(_other.priority), parent(nullptr), active(_other.active)
{
    gameObjects.push_back(this);

    switch (copyType)
    {
    case CopyType::Shallow:
        ShallowCopy(_other);
        break;

    case CopyType::Deep:
        DeepCopy(_other);
        break;
    }

    BubbleSort();
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

void HWGameObject::DeepCopy(const HWGameObject& _other)
{
    std::unique_ptr<HWTransform> transformCp = std::make_unique<HWTransform>(*_other.transform);
    transformCp->gameObject = this;
    hwComponents.push_back(std::move(transformCp));
    transform = GetComponent<HWTransform>();

    // コピー元のComponentのコピーを行う
    for (const auto& cp : _other.hwComponents)
    {
        // HWTransformは無視
        if (typeid(*cp) == typeid(HWTransform)) continue;
        
        // HWRendererの場合はモデルの複製を行う
        if (typeid(*cp) == typeid(HWRenderer))
        {
            // dynamic_castで正確な型に変換し、ディープコピーを行う
            HWRenderer* renderer = dynamic_cast<HWRenderer*>(cp.get());
            if (renderer) 
            {
                auto component = std::make_unique<HWRenderer>(renderer->GetModelHandle());
                // コンポーネントからアタッチされているGameObjectとTransformを確認できるようにする
                component->gameObject = this;
                component->transform = (GetComponent<HWTransform>());
                // 所有権を譲渡
                hwComponents.push_back(std::move(component));
            }
        }
        else
        {
            // そのほかのコンポーネントは通常のコピーを行う
            auto component = std::make_unique<HWComponent>(*cp);
            // コンポーネントからアタッチされているGameObjectとTransformを確認できるようにする
            component->gameObject = this;
            component->transform = (GetComponent<HWTransform>());
            // 所有権を譲渡
            hwComponents.push_back(std::move(component));
        }
    }
}


void HWGameObject::ShallowCopy(const HWGameObject& _other)
{
        // HWTransformのコピー
        auto transformCp = std::make_unique<HWTransform>(*(_other.transform));
        transformCp->gameObject = this;
        hwComponents.push_back(std::move(transformCp));
        transform = GetComponent<HWTransform>();

        for (const auto& cp : _other.hwComponents)
        {
            // HWTransformは無視
            if (typeid(*cp) == typeid(HWTransform)) continue;

            // HWRendererの場合は特定のコンストラクタを呼ぶ
            if (typeid(*cp) == typeid(HWRenderer))
            {
                // dynamic_castで正確な型に変換し、特定のコンストラクタを呼び出す
                HWRenderer* renderer = dynamic_cast<HWRenderer*>(cp.get());
                if (renderer)
                {
                    // HWRendererの特定のコンストラクタを使用して、複製を作成
                    auto component = std::make_unique<HWRenderer>(renderer->GetModelHandle());
                    component->gameObject = this;
                    component->transform = GetComponent<HWTransform>();
                    hwComponents.push_back(std::move(component));
                }
            }
            else
            {
                // そのほかのコンポーネントは通常のコピーを行う
                auto component = std::make_unique<std::decay_t<decltype(*cp)>>(*cp);
                component->gameObject = this;
                component->transform = GetComponent<HWTransform>();
                hwComponents.push_back(std::move(component));
            }
        }

}

void HWGameObject::CallAllUpdates()
{
    if (!active) return;

    for (auto& component : hwComponents)
    {
        if(component->active)
        {
            // まだStartメソッドを実行していない場合は実行する
            if(!component->completedStartMethod)
            {
                component.get()->Start();
                // Startメソッドを実行済みにする
                component->completedStartMethod = true;
            }
            component.get()->Update();
        }
    }
}

void HWGameObject::CallAllOnCollisionEnters(HWCollider& _collider)
{
    if (!active) return;

    for (auto& component : hwComponents)
    {
        if(component->active)
            component.get()->OnCollisionEnterHandler(_collider);
    }
}

void HWGameObject::CallAllOnCollisionStays(HWCollider& _collider)
{
    if (!active) return;

    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->OnCollisionStayHandler(_collider);
    }
}

void HWGameObject::CallAllOnCollisionExits(HWCollider& _collider)
{
    if (!active) return;

    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->OnCollisionExsitHandler(_collider);
    }
}

void HWGameObject::CallAllOnTriggerEnters(HWCollider& _collider)
{
    if (!active) return;

    for (auto& component : hwComponents)
    {
        if(component->active)
            component.get()->OnTriggerEnterHandler(_collider);
    }
}

void HWGameObject::CallAllOnTriggerStays(HWCollider& _collider)
{
    if (!active) return;

    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->OnTriggerStayHandler(_collider);
    }
}

void HWGameObject::CallAllOnTriggerExits(HWCollider& _collider)
{
    if (!active) return;

    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->OnTriggerExsitHandler(_collider);
    }
}


#pragma endregion

#pragma region publicメソッド



HWGameObject* HWGameObject::GetChild(const int _index)
{
    if (_index >= 0 && _index < children.size())
        return children[_index];
    return nullptr;
}

void HWGameObject::SetParent(HWGameObject* _parent)
{
    // すでに親オブジェクトが存在する場合、親子関係を解消する
    if (parent != nullptr)
    {
        auto it = std::find(parent->children.begin(), parent->children.end(), this);
        if (it != parent->children.end())
        {
            parent->children.erase(it);
            parent = nullptr;
        }
    }

    parent = _parent;
    // 親オブジェクトの子オブジェクトとして登録
    parent->children.push_back(this);
}


#pragma endregion
