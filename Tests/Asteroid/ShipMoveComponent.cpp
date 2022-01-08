#include "ShipMoveComponent.h"
COMPONENT_DEFINITION(Pe2::Component, ShipMoveComponent)
ShipMoveComponent::ShipMoveComponent()
{
}
ShipMoveComponent::~ShipMoveComponent()
{
}

void ShipMoveComponent::Init()
{
    REQUIRED_COMPONENT(Pe2::TransformComponent);
}

void ShipMoveComponent::ProcessInput(const Pe2::InputDevice *inputDevice)
{
    if (inputDevice->keyboard.GetKeyState(Pe2::KEYCODE_W) == Pe2::ButtonState::HOLD)
        moveForward = true;
    else
        moveForward = false;

    if (inputDevice->keyboard.GetKeyState(Pe2::KEYCODE_S) == Pe2::ButtonState::HOLD)
        moveBackward = true;
    else
        moveBackward = false;

    if (inputDevice->keyboard.GetKeyState(Pe2::KEYCODE_A) == Pe2::ButtonState::HOLD)
        rotLeft = true;
    else
        rotLeft = false;

    if (inputDevice->keyboard.GetKeyState(Pe2::KEYCODE_D) == Pe2::ButtonState::HOLD)
        rotRight = true;
    else
        rotRight = false;
}

void ShipMoveComponent::Update(float deltaTime) 
{
    if (!ownerTransformComponent)
        ownerTransformComponent = GetOwner()->GetComponent<Pe2::TransformComponent>();

    if (moveForward)
        ownerTransformComponent->Translate(ownerTransformComponent->GetLocalAxisX() * moveSpeed * deltaTime);
    if (moveBackward)
        ownerTransformComponent->Translate(-ownerTransformComponent->GetLocalAxisX() * moveSpeed * deltaTime);

    if (rotLeft)
        ownerTransformComponent->Rotate(rotSpeed * deltaTime);

    if (rotRight)
        ownerTransformComponent->Rotate(-rotSpeed * deltaTime);
}