#include "CameraComponent.h"
#include "Math/MathUtils.h"
#include "Entity.h"
namespace mulberry
{
    CameraComponent::CameraComponent(int32_t updateOrder)
        : Component(updateOrder)
    {
        mCamera.viewMat = Mat4::LookAt(Vec2::ZERO, 0.0f);
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
        // only update viewmat while transform was updated
        auto t = GetOwner()->GetComponent<TransformComponent>()->GetTransform();
        if (mPreTransform != t)
        {
            mPreTransform = t;
            mCamera.viewMat = Mat4::LookAt(mPreTransform.position, mPreTransform.rotation);
        }
        return mCamera.viewMat;
    }
    const Mat4 &CameraComponent::GetProjMat() const
    {
        return mCamera.projMat;
    }

    void CameraComponent::SetClearColor(const Color &color)
    {
        mCamera.clearColor = color;
    }

    const Color &CameraComponent::GetClearColor() const
    {
        return mCamera.clearColor;
    }

    void CameraComponent::SetViewport(const Viewport &viewport)
    {
        mCamera.viewport=viewport;
        float halfWidth = mCamera.viewport.width / 2.0f;
        float halfHeight = mCamera.viewport.height / 2.0f;
        mCamera.projMat = Mat4::Ortho(-halfWidth, halfWidth, halfHeight, -halfHeight, 0.1f, 1000.0f);
    }
    const Viewport &CameraComponent::GetViewport() const
    {
        return mCamera.viewport;
    }

    Vec2 CameraComponent::GetExtent() const
    {
        return Vec2(mCamera.viewport.width, mCamera.viewport.height);
    }
}
