#pragma once
#include "libPe2/libPe2.h"
class ShipMoveComponent : Pe2::Component
{
    COMPONENT_DECLARATION()

public:
    ShipMoveComponent()
    {
    }
    ~ShipMoveComponent()
    {
    }

    void Update(float deltaTime) override
    {
        Pe2::TransformComponent *ownerTransformComponent = GetOwner()->GetComponent<Pe2::TransformComponent>();
        if (Pe2::Input::GetKeyboard()->GetKeyState(Pe2::KEYCODE_W) == Pe2::ButtonState::PRESS)
            ownerTransformComponent->Translate(ownerTransformComponent->GetLocalAxisY() * speed * deltaTime);
    }

protected:
    friend class Pe2::Entity;
    void DefineRequiredComponents() override
    {
        REQUIRED_COMPONENT(Pe2::TransformComponent);
    }

private:
    float speed = 10;
};