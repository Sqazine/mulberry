#include "Entity.h"
#include "Logger.h"
#include "Scene.h"
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
        for (const auto &c : mComponents)
        {
            std::string cName = typeid(*c).name();
            std::string componentName = typeid(*component).name();
            if (cName == componentName)
            {
                MULBERRY_WARN("[API:AddComponent(in Entity) return false]:Cannot Add a component(type={}) to entity '{}',already exists a same type component", componentName, mName);
                return false;
            }
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

    AssetManager *Entity::GetSceneAssetManager() const
    {
        return GetOwner()->GetSceneAssetManager();
    }
}