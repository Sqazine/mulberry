#pragma once
#include "Component.h"
#include "Math/Mat4.h"
#include "Math/Vec2.h"
#include "Math/Color.h"
#include "../Entity.h"
#include "TransformComponent.h"
namespace Pe2
{
    struct Camera
    {
        Color clearColor;
        Vec2 extent;
    };
    class CameraComponent : public Component
    {
        COMPONENT_DECLARATION()
    public:
        CameraComponent(int32_t updateOrder = 5);
        ~CameraComponent();

        void Init() override;

        const Mat4& GetViewMat();
        const Mat4& GetProjMat() const;

        void SetClearColor(const Color &color);
        const Color &GetClearColor() const;

        void SetExtent(const Vec2& extent);
        const Vec2 &GetExtent() const;

    private:
        struct Camera mCamera;
        Transform mPreTransform;
        Mat4 mProjMat;
        Mat4 mViewMat;
    };
}