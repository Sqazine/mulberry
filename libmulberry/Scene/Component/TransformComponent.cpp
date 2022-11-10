#include "TransformComponent.h"
namespace mulberry
{
    TransformComponent::TransformComponent(int32_t updateOrder)
        : Component(updateOrder)
    {
    }

    TransformComponent::~TransformComponent()
    {
    }

    void TransformComponent::SetPosition(const Vec2 &pos)
    {
        mTransform.position = pos;
    }

    void TransformComponent::SetPosition(float posX, float posY)
    {
        mTransform.position = Vec2(posX, posY);
    }

    const Vec2 &TransformComponent::GetPosition() const
    {
        return mTransform.position;
    }

    void TransformComponent::Translate(const Vec2 &pos)
    {
        mTransform.position = Vec2::Translate(mTransform.position, pos);
    }

    void TransformComponent::SetRotation(float degree)
    {
        mTransform.rotation = degree;
    }

    float TransformComponent::GetRotation() const
    {
        return mTransform.rotation;
    }

    void TransformComponent::Rotate(float degree)
    {
        mTransform.rotation += degree;
    }

    void TransformComponent::SetScale(float scale)
    {
        mTransform.scale.x = mTransform.scale.y = scale;
    }

    void TransformComponent::SetScale(const Vec2 &scale)
    {
        mTransform.scale = scale;
    }

    void TransformComponent::SetScale(float scaleX, float scaleY)
    {
        mTransform.scale.x = scaleX;
        mTransform.scale.y = scaleY;
    }

    const Vec2 &TransformComponent::GetScale() const
    {
        return mTransform.scale;
    }

    Vec2 TransformComponent::GetLocalAxisX() const
    {
        return Vec2::Rotate(Vec2::UNIT_X, MathUtils::ToRadian(mTransform.rotation));
    }

    Vec2 TransformComponent::GetLocalAxisY() const
    {
        return Vec2::Rotate(Vec2::UNIT_Y, MathUtils::ToRadian(mTransform.rotation));
    }

    Mat4 TransformComponent::GetModelMat() const
    {
        return mTransform.ToMat4();
    }

    const Transform &TransformComponent::GetTransform() const
    {
        return mTransform;
    }

}