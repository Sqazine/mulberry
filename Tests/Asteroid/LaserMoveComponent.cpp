#include "LaserMoveComponent.h"

LaserMoveComponent::LaserMoveComponent()
{
}
LaserMoveComponent::~LaserMoveComponent()
{
}

void LaserMoveComponent::Init()
{
    RequiredComponent<mulberry::TransformComponent>();
    RequiredComponent<mulberry::SpriteComponent>();

    if (!mOwnerSpriteComponent)
        mOwnerSpriteComponent = GetOwner()->GetComponent<mulberry::SpriteComponent>();

    if (!mOwnerTransformComponent)
        mOwnerTransformComponent = GetOwner()->GetComponent<mulberry::TransformComponent>();
}

void LaserMoveComponent::Update()
{
    float deltaTime = mulberry::App::GetInstance().GetTimer()->GetDeltaTime();

    auto nextPos = moveDir * moveSpeed * deltaTime;

    mOwnerTransformComponent->Translate(nextPos);
}

void LaserMoveComponent::SetDir(const mulberry::Vec2& dir)
{
    moveDir=dir;
}