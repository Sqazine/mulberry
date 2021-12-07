#pragma once
#include "Component.h"
#include "Math/Mat4.h"
#include "Math/Vec2.h"
#include "Math/Color.h"
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
        CameraComponent(int updateOrder=5);
        ~CameraComponent();

        Mat4 GetViewMat() const;
        Mat4 GetProjMat() const;

        const Vec2 &GetCameraExtent() const;
        const Color &GetClearColor() const;

    private:
        struct Camera m_Camera;
    };
}