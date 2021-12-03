#include "Entity.h"

namespace Pe2
{

    Entity::Entity()
        : m_Visiable(true), m_Name("Entity")
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
}