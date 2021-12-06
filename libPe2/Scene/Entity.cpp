#include "Entity.h"

namespace Pe2
{

    Entity::Entity(std::string_view name)
        : Object(name), m_Visiable(true),m_IsStatic(false)
    {
    }

    Entity::~Entity()
    {
        RemoveAllComponents();
    }

    void Entity::RemoveAllComponents()
    {
        std::vector<std::unique_ptr<Component>>().swap(m_Components);
    }

    void Entity::SetVisiable(bool visiable)
    {
        m_Visiable = visiable;
    }
    bool Entity::IsVisiable() const
    {
        return m_Visiable;
    }

    void Entity::SetStatic(bool isStatic)
    {
        m_IsStatic = isStatic;
    }
    bool Entity::IsStatic() const
    {
        return m_IsStatic;
    }
}