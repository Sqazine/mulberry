#pragma once
#include "Color.h"
#include "Graphics/RHI/Viewport.h"
#include "Math/Mat4.h"
namespace mulberry
{
    struct Camera
    {
        Color clearColor;
        Viewport viewport;
        Mat4 projMat;
        Mat4 viewMat;
    };
}