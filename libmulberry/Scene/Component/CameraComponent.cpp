#include "CameraComponent.h"
#include "Math/MathUtils.h"
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace mulberry
{
    CameraComponent::CameraComponent(int32_t updateOrder)
        : Component(updateOrder)
    {
        mViewMat = Mat4::LookAt(Vec2::ZERO, 0.0f);
    }
    CameraComponent::~CameraComponent()
    {
    }

    void CameraComponent::Init()
    {
        RequiredComponent<TransformComponent>();
    }

    const Mat4 &CameraComponent::GetViewMat()
    {
        //only update viewmat while transform was updated
        auto t = GetOwner()->GetComponent<TransformComponent>()->GetTransform();
        if (mPreTransform != t)
        {
            mPreTransform = t;
            mViewMat = Mat4::LookAt(mPreTransform.position, mPreTransform.rotation);
        }
        return mViewMat;
    }
    const Mat4 &CameraComponent::GetProjMat() const
    {
        return mProjMat;
    }

    void CameraComponent::SetClearColor(const Color &color)
    {
        mCamera.clearColor = color;
    }

    const Color &CameraComponent::GetClearColor() const
    {
        return mCamera.clearColor;
    }

    void CameraComponent::SetExtent(const Vec2 &extent)
    {
        mCamera.extent = extent;
        float halfWidth = mCamera.extent.x / 2.0f;
        float halfHeight = mCamera.extent.y / 2.0f;
        mProjMat = Mat4::Ortho(-halfWidth, halfWidth, halfHeight, -halfHeight, 0.1f, 1000.0f);
    }
    const Vec2 &CameraComponent::GetExtent() const
    {
        return mCamera.extent;
    }
}
