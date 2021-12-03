#pragma once
#include "Component.h"
#include "../../Math/Mat4.h"
#include "../../Math/Vec2.h"
#include "../../Math/Color.h"
namespace Pe2
{
    struct Camera
    {
        Color clearColor;
        Vec2 position;
        Vec2 extent;
    };

    class CameraComponent : public Component
    {
        COMPONENT_DECLARATION()
    public:
        CameraComponent();
        ~CameraComponent();

    private:
        
    };
}