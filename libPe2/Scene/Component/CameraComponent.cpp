#include "CameraComponent.h"
#include "Math/MathUtils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

    const Mat4& CameraComponent::GetViewMat() 
    {
        //only update viewmat while transform was updated
        auto t=GetOwner()->GetComponent<TransformComponent>()->GetTransform();
        if (m_PreTransform != t)
        {
            m_PreTransform = t;
            m_ViewMat = Mat4::LookAt(m_PreTransform.position,m_PreTransform.rotation);
        }
        return m_ViewMat;
    }
    const Mat4& CameraComponent::GetProjMat() const
    {
       
        return m_ProjMat;
    }

    void CameraComponent::SetClearColor(const Color &color)
    {
        m_Camera.clearColor = color;
    }

    const Color &CameraComponent::GetClearColor() const
    {
        return m_Camera.clearColor;
    }

    void CameraComponent::SetExtent(const Vec2 &extent)
    {
        m_Camera.extent = extent;
         float halfWidth = m_Camera.extent.x / 2.0f;
        float halfHeight = m_Camera.extent.y / 2.0f;
        m_ProjMat=Mat4::Ortho(-halfWidth, halfWidth, halfHeight, -halfHeight, 0.1f, 1000.0f);
    }
    const Vec2 &CameraComponent::GetExtent() const
    {
        return m_Camera.extent;
    }

    void CameraComponent::DefineRequiredComponents()
    {
        REQUIRED_COMPONENT(TransformComponent)
    }
}
