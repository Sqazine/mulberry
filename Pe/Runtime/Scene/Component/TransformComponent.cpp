#include "TransformComponent.h"

COMPONENT_DEFINITION(Component, TransformComponent)

TransformComponent::TransformComponent(int updateOrder)
    : Component(updateOrder)
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetPosition(const Vec2 &pos)
{
    m_Transform.position = pos;
}

void TransformComponent::SetPosition(float posX, float posY)
{
    m_Transform.position = Vec2(posX, posY);
}

const Vec2 &TransformComponent::GetPosition() const
{
    return m_Transform.position;
}

void TransformComponent::Translate(const Vec2 &pos)
{
    m_Transform.position = Vec2::Translate(m_Transform.position, pos);
}

void TransformComponent::SetRotation(float radian)
{
    m_Transform.rotation = radian;
}

float TransformComponent::GetRotation() const
{
    return m_Transform.rotation;
}

void TransformComponent::Rotate(float radian)
{
    m_Transform.rotation += radian;
}

void TransformComponent::SetScale(float scale)
{
    m_Transform.scale.x = m_Transform.scale.y = scale;
}

void TransformComponent::SetScale(const Vec2 &scale)
{
    m_Transform.scale = scale;
}

void TransformComponent::SetScale(float scaleX, float scaleY)
{
    m_Transform.scale.x = scaleX;
    m_Transform.scale.y = scaleY;
}

const Vec2 &TransformComponent::GetScale() const
{
    return m_Transform.scale;
}

Vec2 TransformComponent::GetLocalAxisX() const
{
    return Vec2::Rotate(m_Transform.rotation);
}

Vec2 TransformComponent::GetLocalAxisY() const
{
    return Vec2::Rotate(m_Transform.rotation + Math::ToRadian(90.0f));
}

Mat4 TransformComponent::GetTransformMatrix() const
{
    return Mat4::Translate(m_Transform.position) * Mat4::Rotate(Math::ToRadian(m_Transform.rotation)) * Mat4::Scale(m_Transform.scale);
}