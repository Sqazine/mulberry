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

        Mat4 GetViewMat() const;
        Mat4 GetProjMat() const;

        const Vec2 &GetCameraExtent() const;
        const Color &GetClearColor() const;

    protected:
        friend class Entity;
        void DefineRequiredComponents() override;
    private:
        struct Camera m_Camera;
    };
}