#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "../../Input/Input.h"
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
#define REQUIRED_COMPONENT(comp)                     \
    if (GetOwner()->GetComponent<comp>() == nullptr) \
        GetOwner()->CreateComponent<comp>();

    class Component
    {
    public:
        Component(int32_t updateOrder = 100);
        virtual ~Component();

        virtual void ProcessInput(const InputDevice* inputDevice);
        virtual void Update(float deltaTime);
        virtual void LateUpdate(float deltaTime);
        virtual void FixedUpdate();

        int32_t GetUpdateOrder() const;

        class Entity *GetOwner() const;

        virtual bool IsSameComponentType(const std::string &comonentType) const;
        static std::string m_ComponentType;

    protected:
        friend class Entity;
        virtual void DefineRequiredComponents() {}

    private:
        friend class Entity;
        int32_t m_UpdateOrder;
        class Entity *m_Owner;
    };
}