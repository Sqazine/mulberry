#include "Entity.h"

namespace mulberry
{

    Entity::Entity(std::string_view name)
        : Object(name), mVisiable(true), mIsStatic(false)
    {
    }

    Entity::~Entity()
    {
        RemoveAllComponents();
    }

    bool Entity::AddComponent(Component *component)
    {
        component->mOwner = this;
        component->Init();
        for (int32_t pos = 0; pos < mComponents.size(); ++pos)
        {
            if (mComponents[pos].get()->IsSameComponentType(component->mComponentType))
                return false;
        }

        auto iter = mComponents.begin();
        for (; iter != mComponents.end(); ++iter)
            if (component->GetUpdateOrder() < (**iter).GetUpdateOrder())
                break;

        auto uniComp = std::unique_ptr<Component>(component);

        mComponents.insert(iter, std::move(uniComp));
        return true;
    }

    void Entity::RemoveAllComponents()
    {
        std::vector<std::unique_ptr<Component>>().swap(mComponents);
    }

    std::vector<Component *> Entity::GetAllComponents() const
    {
        std::vector<Component *> result;
        for (const auto &c : mComponents)
            result.emplace_back(c.get());
        return result;
    }

    void Entity::SetVisiable(bool visiable)
    {
        mVisiable = visiable;
    }
    bool Entity::IsVisiable() const
    {
        return mVisiable;
    }

    void Entity::SetStatic(bool isStatic)
    {
        mIsStatic = isStatic;
    }
    bool Entity::IsStatic() const
    {
        return mIsStatic;
    }

    Scene *Entity::GetOwner() const
    {
        return mOwner;
    }
}