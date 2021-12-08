#include "CameraComponent.h"
#include "Math/MathUtils.h"
namespace Pe2
{
    COMPONENT_DEFINITION(Component, CameraComponent)

    CameraComponent::CameraComponent(int32_t updateOrder)
        : Component(updateOrder)
    {
    }
    CameraComponent::~CameraComponent()
    {
    }

    Mat4 CameraComponent::GetViewMat() const
    {
        return Mat4::LookAt(GetOwner()->GetComponent<TransformComponent>()->GetPosition(), MathUtils::ToRadian(GetOwner()->GetComponent<TransformComponent>()->GetRotation()));
    }
    Mat4 CameraComponent::GetProjMat() const
    {
        float halfWidth = m_Camera.extent.x / 2.0f;
        float halfHeight = m_Camera.extent.y / 2.0f;
        return Mat4::Ortho(-halfWidth, halfWidth, halfHeight, -halfHeight, 0.01f, 100.0f);
    }

    const Vec2 &CameraComponent::GetCameraExtent() const
    {
        return m_Camera.extent;
    }

    const Color &CameraComponent::GetClearColor() const
    {
        return m_Camera.clearColor;
    }

    void CameraComponent::DefineRequiredComponents()
    {
        REQUIRED_COMPONENT(TransformComponent)
    }
}
