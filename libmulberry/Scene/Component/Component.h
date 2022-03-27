#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "../../Input.h"
namespace mulberry
{

#define TO_STRING(x) #x

#define COMPONENT_DECLARATION()         \
public:                                 \
    static std::string mComponentType; \
    virtual bool IsSameComponentType(const std::string &comonentType) const override;

#define COMPONENT_DEFINITION(parentCompName, childCompName)                             \
    std::string childCompName::mComponentType = std::string(TO_STRING(childCompName)); \
    bool childCompName::IsSameComponentType(const std::string &comonentType) const      \
    {                                                                                   \
        if (childCompName::mComponentType == comonentType)                             \
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

        virtual void Init();
        virtual void ProcessInput(const InputDevice *inputDevice);
        virtual void Update(float deltaTime);
        virtual void LateUpdate(float deltaTime);
        virtual void FixedUpdate();

        int32_t GetUpdateOrder() const;

        class Entity *GetOwner() const;
        class Scene* GetScene() const;
        class AssetManager* GetSceneAssetManager() const;
    protected:
        friend class Entity;
        virtual bool IsSameComponentType(const std::string &comonentType) const;
        static std::string mComponentType;

    private:
        friend class Entity;
        int32_t mUpdateOrder;
        class Entity *mOwner;
    };
}