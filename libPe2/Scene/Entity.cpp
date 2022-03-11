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

     bool Entity::AddComponent(Component* component)
     {
        component->m_Owner = this;
        component->Init();
        for (int32_t pos = 0; pos < m_Components.size(); ++pos)
        {
           if (m_Components[pos].get()->IsSameComponentType(component->m_ComponentType))
               return false;
        }

        auto iter = m_Components.begin();
        for (; iter != m_Components.end(); ++iter)
            if (component->GetUpdateOrder() < (**iter).GetUpdateOrder())
                break;

        auto uniComp=std::unique_ptr<Component>(component);
                
        m_Components.insert(iter, std::move(uniComp));
        return true;
     }

    void Entity::RemoveAllComponents()
    {
        std::vector<std::unique_ptr<Component>>().swap(m_Components);
    }

    std::vector<Component*> Entity::GetAllComponents() const
    {
        std::vector<Component*> result;
        for(const auto& c:m_Components)
            result.emplace_back(c.get());
        return result;
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