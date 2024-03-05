#pragma once
#include "Component.h"
#include "Math/Mat4.h"
#include "Vec2.h"
#include "TransformComponent.h"
#include "Graphics/Camera.h"
namespace mulberry
{
    class CameraComponent : public Component
    {
    public:
        CameraComponent(int32_t updateOrder = 5);
        ~CameraComponent();

        void Init() override;

        const Mat4& GetViewMat();
        const Mat4& GetProjMat() const;

        void SetClearColor(const Color &color);
        const Color &GetClearColor() const;

        void SetViewport(const Viewport& viewport);
        const Viewport &GetViewport() const;

        Vec2 GetExtent() const;

    private:
        Camera mCamera;
        Transform mPreTransform;
        
    };
}