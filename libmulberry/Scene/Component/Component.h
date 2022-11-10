#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Input.h"
namespace mulberry
{
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

    private:
        friend class Entity;
        int32_t mUpdateOrder;
        class Entity *mOwner;
    };
}