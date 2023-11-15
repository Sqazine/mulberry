#pragma once
#include "mulberry/mulberry.h"

class LaserMoveComponent : public mulberry::Component
{
public:
    LaserMoveComponent();
    ~LaserMoveComponent();

    void Init() override;
    void Update() override;

    void SetDir(const mulberry::Vec2& dir);

private:
    mulberry::TransformComponent *mOwnerTransformComponent = nullptr;
    mulberry::SpriteComponent *mOwnerSpriteComponent = nullptr;

    float moveSpeed = 1500;
    mulberry::Vec2 moveDir;
};
