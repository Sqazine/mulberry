#pragma once
#include "libmulberry/libmulberry.h"
class ShipMoveComponent : public mulberry::Component
{
public:
    ShipMoveComponent();
    ~ShipMoveComponent();

    void Init() override;
    void ProcessInput(const mulberry::InputDevice *inputDevice) override;
    void Update(float deltaTime) override;
private:
    mulberry::TransformComponent *ownerTransformComponent = nullptr;
    mulberry::SpriteComponent *ownerSpriteComponent = nullptr;

    std::unique_ptr<mulberry::GL::Texture> movingTexture;
    std::unique_ptr<mulberry::GL::Texture> staticTexture;

    float moveSpeed = 500;
    float rotSpeed = 200;
    bool moveForward = false;
    bool moveBackward = false;
    bool rotLeft = false;
    bool rotRight = false;
};

