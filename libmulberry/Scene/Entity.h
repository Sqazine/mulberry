#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Component/Component.h"
#include "Object.h"
namespace mulberry
{
    class Entity : public Object
    {
    public:
        Entity(std::string_view name);
        ~Entity();

        bool AddComponent(Component* component);

        template <class T, typename... Args>
        T *CreateComponent(Args &&...params);

        template <class T>
        bool RemoveComponent();
        void RemoveAllComponents();

        template <class T>
        T *GetComponent() const;

        std::vector<Component *> GetAllComponents() const;

        void SetVisiable(bool visiable);
        bool IsVisiable() const;

        void SetStatic(bool isStatic);
        bool IsStatic() const;

        class Scene *GetOwner() const;

    private:
        friend class Scene;

        class Scene *mOwner;

        bool mVisiable;
        bool mIsStatic;
        std::vector<std::unique_ptr<Component>> mComponents;
    };

    template <class T, typename... Args>
    inline T *Entity::CreateComponent(Args &&...params)
    {
        std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(params)...);
        component->mOwner = this;
        component->Init();
        for (int32_t pos = 0; pos < mComponents.size(); ++pos)
        {
            if (dynamic_cast<T *>(mComponents[pos].get()))
                return nullptr;
        }

        auto iter = mComponents.begin();
        for (; iter != mComponents.end(); ++iter)
            if (component.get()->GetUpdateOrder() < (**iter).GetUpdateOrder())
                break;

        T *result = component.get();
        mComponents.insert(iter, std::move(component));
        return result;
    }

    template <class T>
    inline bool Entity::RemoveComponent()
    {
        if (mComponents.empty())
            return false;

        auto iter = std::find_if(mComponents.begin(), mComponents.end(), [](auto &component)
                                 { return component.get()->IsSameComponentType(T::mComponentType); });

        bool success = iter != mComponents.end();
        if (success)
            mComponents.erase(iter);
    }

    template <class T>
    inline T *Entity::GetComponent() const
    {
        if (mComponents.empty())
            return nullptr;

        auto iter = std::find_if(mComponents.begin(), mComponents.end(), [](auto &component)
                                 { return dynamic_cast<T *>(component.get()) != nullptr; });

        bool success = iter != mComponents.end();
        if (success)
            return dynamic_cast<T *>((*(iter)).get());
        return nullptr;
    }
}