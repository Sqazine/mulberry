#pragma once
#include "libPe2/libPe2.h"
class ShipMoveComponent : public Pe2::Component
{
    COMPONENT_DECLARATION()

public:
    ShipMoveComponent();
    ~ShipMoveComponent();

    void Init() override;
    void ProcessInput(const Pe2::InputDevice *inputDevice) override;
    void Update(float deltaTime) override;

private:
    Pe2::TransformComponent *ownerTransformComponent = nullptr;
    float moveSpeed = 500;
    float rotSpeed = 200;
    bool moveForward = false;
    bool moveBackward = false;
    bool rotLeft = false;
    bool rotRight = false;
};