#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace Pe2
{

#define TO_STRING(x) #x

#define COMPONENT_DECLARATION()         \
public:                                 \
    static std::string m_ComponentType; \
    virtual bool IsSameComponentType(const std::string &comonentType) const override;

#define COMPONENT_DEFINITION(parentCompName, childCompName)                             \
    std::string childCompName::m_ComponentType = std::string(TO_STRING(childCompName)); \
    bool childCompName::IsSameComponentType(const std::string &comonentType) const      \
    {                                                                                   \
        if (childCompName::m_ComponentType == comonentType)                             \
            return true;                                                                \
        return parentCompName::IsSameComponentType(comonentType);                       \
    }
    #define REQUIRED_COMPONENT(comp) \
    m_RequiredComponents.emplace_back(std::string(TO_STRING(comp)));

    class Component
    {
    public:
        Component(int updateOrder = 100);
        virtual ~Component();

        virtual void ProcessInput();
        virtual void Update(float deltaTime);
        virtual void LateUpdate(float deltaTime);
        virtual void FixedUpdate();

        int GetUpdateOrder() const;

        const class Entity *GetOwner() const;

        virtual bool IsSameComponentType(const std::string &comonentType) const;
        static std::string m_ComponentType;

    protected:
        friend class Entity;
        std::vector<std::string> m_RequiredComponents;

    private:
        friend class Entity;
        int m_UpdateOrder;
        const class Entity *m_Owner;
    };
}