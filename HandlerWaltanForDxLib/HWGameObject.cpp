#include "h/HWGameObject.h"


/**
* @author   NZ
* @date     24/07/29
* @note		HWGameObject�̎����t�@�C��
*/


// �ÓI�����o�ϐ��̏�����
std::vector<HWGameObject*> HWGameObject::gameObjects;
std::vector<HWGameObject::PendingDestroy> HWGameObject::destroyList;


#pragma region �R���X�g���N�^


HWGameObject::HWGameObject() : priority(0), name("hwObj"), tag(0), parent(nullptr), active(true)
{
    gameObjects.push_back(this);

    std::unique_ptr<HWTransform> transformCp = std::make_unique<HWTransform>();
    transformCp->gameObject = this;
    transformCp->Awake();
    hwComponents.push_back(std::move(transformCp));
    transform = GetComponent<HWTransform>();

    BubbleSort();
}

HWGameObject::HWGameObject(const std::string& _name) : priority(0), name(_name), tag(0), parent(nullptr),
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

HWGameObject::HWGameObject(int _priority) : priority(_priority), name("hwObj"), tag(0), parent(nullptr),
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

HWGameObject::HWGameObject(const std::string& _name, int _priority) : name(_name), tag(0), priority(_priority),
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
                           tag(_other.tag), priority(_other.priority), parent(nullptr), active(_other.active)
{
    gameObjects.push_back(this);

    switch (copyType)
    {
    case CopyType::Shallow:
        // ������(DeepCopy�̏����ƈꏏ)
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
    for (const auto& cp : hwComponents)
        cp->OnDestroy();

    auto it = std::find(gameObjects.begin(), gameObjects.end(), this);
    if (it != gameObjects.end())
        gameObjects.erase(it);
}


#pragma region private���\�b�h


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

    // �R�s�[����Component�̃R�s�[���s��
    for (const auto& cp : _other.hwComponents)
    {
        // HWTransform�͖���
        if (typeid(*cp) == typeid(HWTransform)) continue;
        
        // HWRenderer�̏ꍇ�̓��f���̕������s��
        if (typeid(*cp) == typeid(HWRenderer))
        {
            // dynamic_cast�Ő��m�Ȍ^�ɕϊ����A�f�B�[�v�R�s�[���s��
            HWRenderer* renderer = dynamic_cast<HWRenderer*>(cp.get());
            if (renderer) 
            {
                auto component = std::make_unique<HWRenderer>(renderer->GetModelHandle());
                // �R���|�[�l���g����A�^�b�`����Ă���GameObject��Transform���m�F�ł���悤�ɂ���
                component->gameObject = this;
                component->transform = (GetComponent<HWTransform>());
                // ���L�������n
                hwComponents.push_back(std::move(component));
            }
        }
        else
        {
            // ���̂ق��̃R���|�[�l���g�͒ʏ�̃R�s�[���s��
            auto component = std::make_unique<HWComponent>(*cp);
            // �R���|�[�l���g����A�^�b�`����Ă���GameObject��Transform���m�F�ł���悤�ɂ���
            component->gameObject = this;
            component->transform = (GetComponent<HWTransform>());
            // ���L�������n
            hwComponents.push_back(std::move(component));
        }
    }
}


void HWGameObject::ShallowCopy(const HWGameObject& _other)
{
        // HWTransform�̃R�s�[
        auto transformCp = std::make_unique<HWTransform>(*(_other.transform));
        transformCp->gameObject = this;
        hwComponents.push_back(std::move(transformCp));
        transform = GetComponent<HWTransform>();

        for (const auto& cp : _other.hwComponents)
        {
            // HWTransform�͖���
            if (typeid(*cp) == typeid(HWTransform)) continue;

            // HWRenderer�̏ꍇ�͓���̃R���X�g���N�^���Ă�
            if (typeid(*cp) == typeid(HWRenderer))
            {
                // dynamic_cast�Ő��m�Ȍ^�ɕϊ����A����̃R���X�g���N�^���Ăяo��
                HWRenderer* renderer = dynamic_cast<HWRenderer*>(cp.get());
                if (renderer)
                {
                    // HWRenderer�̓���̃R���X�g���N�^���g�p���āA�������쐬
                    auto component = std::make_unique<HWRenderer>(renderer->GetModelHandle());
                    component->gameObject = this;
                    component->transform = GetComponent<HWTransform>();
                    hwComponents.push_back(std::move(component));
                }
            }
            else
            {
                // ���̂ق��̃R���|�[�l���g�͒ʏ�̃R�s�[���s��
                auto component = std::make_unique<std::decay_t<decltype(*cp)>>(*cp);
                component->gameObject = this;
                component->transform = GetComponent<HWTransform>();
                hwComponents.push_back(std::move(component));
            }
        }

}

void HWGameObject::CallTransformUpdate()
{
    transform->Update();
}

void HWGameObject::CallAllUpdates()
{
    if (!active) return;

    for (auto& component : hwComponents)
    {
        // HWTransform�͖���
        if (typeid(*component) == typeid(HWTransform)) continue;

        if(component->active)
        {
            // �܂�Start���\�b�h�����s���Ă��Ȃ��ꍇ�͎��s����
            if(!component->completedStartMethod)
            {
                component.get()->Start();
                // Start���\�b�h�����s�ς݂ɂ���
                component->completedStartMethod = true;
            }
            component.get()->Update();
        }
    }
}

void HWGameObject::CallAllLateUpdates()
{
    if (!active) return;

    for (auto& component : hwComponents)
    {
        if (component->active)
            component.get()->LateUpdate();
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

#pragma region public���\�b�h



HWGameObject* HWGameObject::GetChild(const int _index)
{
    if (_index >= 0 && _index < children.size())
        return children[_index];
    return nullptr;
}

void HWGameObject::SetParent(HWGameObject* _parent, const bool _isAffect)
{
    // ���łɐe�I�u�W�F�N�g�����݂���ꍇ�A�e�q�֌W����������
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
    // �e�I�u�W�F�N�g�̎q�I�u�W�F�N�g�Ƃ��ēo�^
    parent->children.push_back(this);
    isAffect = _isAffect;
}

void HWGameObject::Destroy(HWGameObject* _obj, float delay)
{
    // ���ɍ폜���X�g�ɓo�^����Ă��邩�𒲂ׂ�
    auto it = std::find_if(destroyList.begin(), destroyList.end(), [_obj](const PendingDestroy& item) {
        return item.object == _obj;
        });

    // �o�^����Ă��Ȃ��ꍇ�͗v�f��ǉ�����
    if(it == destroyList.end())
        destroyList.push_back({ _obj, GetNowCount() + static_cast<int>(delay * 1000) });
    // ���ɓo�^����Ă���ꍇ�́A�폜���Ԃ��㏑��
    else if (it != destroyList.end())
        it->time = GetNowCount() + static_cast<int>(delay * 1000);
}


#pragma endregion
