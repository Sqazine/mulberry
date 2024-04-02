#pragma once
#include "mulberry.h"
class ShipMoveComponent : public mulberry::Component
{
public:
    ShipMoveComponent();
    ~ShipMoveComponent();

    void Init() override;
    void Update() override;

    void Move();
private:
    mulberry::TransformComponent *mOwnerTransformComponent = nullptr;
    mulberry::SpriteComponent *mOwnerSpriteComponent = nullptr;
    mulberry::CameraComponent *mCameraComponent = nullptr;

    std::unique_ptr<mulberry::Texture> movingTexture;
    std::unique_ptr<mulberry::Texture> staticTexture;

    float moveSpeed = 500;
    float rotSpeed = 200;
    bool moveForward = false;
    bool moveBackward = false;
};

