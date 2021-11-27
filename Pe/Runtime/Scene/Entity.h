#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Component/Component.h"

class Entity
{
public:
    Entity();
    virtual ~Entity();

    virtual void ProcessInput(class InputState *state);
    virtual void Update(float deltaTime);

    template <class T, typename... Args>
    void AddComponent(Args &&...params);

    template <class T>
    bool RemoveComponent();
    void RemoveAllComponents();

    template <class T>
    T *GetComponent() const;

    void SetVisiable(bool visiable);
    bool IsVisiable() const;

    
private:
    bool m_Visiable;
    std::string m_Name;
    std::vector<std::unique_ptr<Component>> m_Components;
};

template <class T, typename... Args>
inline void Entity::AddComponent(Args &&...params)
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
    {
        if (component.get()->GetUpdateOrder() < (**iter).GetUpdateOrder())
            break;
    }
    m_Components.insert(iter, std::move(component));
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