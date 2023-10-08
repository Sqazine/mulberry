#pragma once
#include "libmulberry/libmulberry.h"

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

    float moveSpeed = 500;
    mulberry::Vec2 moveDir;
};
