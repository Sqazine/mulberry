#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Platform/Input.h"
namespace mulberry
{
    class Component
    {
    public:
        Component(int32_t updateOrder = 100);
        virtual ~Component();

        virtual void Init();
        virtual void ProcessInput(const Input *input);
        virtual void Update(float deltaTime);
        virtual void LateUpdate(float deltaTime);
        virtual void FixedUpdate();

        int32_t GetUpdateOrder() const;

        class Entity *GetOwner() const;
        class Scene *GetScene() const;
        class AssetManager *GetSceneAssetManager() const;

        template <typename T, typename... Args>
        T *RequiredComponent(Args &&...params);

    private:
        friend class Entity;
        int32_t mUpdateOrder;
        class Entity *mOwner;
    };

    template <typename T, typename... Args>
    inline T *Component::RequiredComponent(Args &&...params)
    {
        auto result = mOwner->GetComponent<T>();
        if (result)
            return result;
        return mOwner->CreateComponent<T>(params...);
    }
}