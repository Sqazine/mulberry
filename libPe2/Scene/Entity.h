#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Component/Component.h"
#include "Object.h"
namespace Pe2
{
    class Entity : public Object
    {
    public:
        Entity(std::string_view name);
        ~Entity();

        template <class T, typename... Args>
        T *CreateComponent(Args &&...params);

        template <class T>
        bool RemoveComponent();
        void RemoveAllComponents();

        template <class T>
        T *GetComponent() const;

        void SetVisiable(bool visiable);
        bool IsVisiable() const;

        void SetStatic(bool isStatic);
        bool IsStatic() const;

    private:
        bool m_Visiable;
        bool m_IsStatic;
        std::vector<std::unique_ptr<Component>> m_Components;
    };

    template <class T, typename... Args>
    inline T *Entity::CreateComponent(Args &&...params)
    {
        std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(params)...);
        component.get()->m_Owner = this;

        for (int pos = 0; pos < m_Components.size(); ++pos)
        {
            if (m_Components[pos].get()->IsSameComponentType(T::m_ComponentType))
            {
                m_Components[pos] = std::move(component);
                return;
            }
        }

        auto iter = m_Components.begin();
        for (; iter != m_Components.end(); ++iter)
            if (component.get()->GetUpdateOrder() < (**iter).GetUpdateOrder())
                break;

        T *result = component.get();
        m_Components.insert(iter, std::move(component));
        return result;
    }

    template <class T>
    inline bool Entity::RemoveComponent()
    {
        if (m_Components.empty())
            return false;

        auto iter = std::find_if(m_Components.begin(), m_Components.end(), [](auto &component)
                                 { return component.get()->IsSameComponentType(T::m_ComponentType); });

        bool success = iter != m_Components.end();
        if (success)
            m_Components.erase(iter);
    }

    template <class T>
    inline T *Entity::GetComponent() const
    {
        if (m_Components.empty())
            return nullptr;

        auto iter = std::find_if(m_Components.begin(), m_Components.end(), [](auto &component)
                                 { return component.get()->IsSameComponentType(T::m_ComponentType); });

        bool success = iter != m_Components.end();
        if (success)
            return static_cast<T *>((*(iter)).get());
        return nullptr;
    }
}