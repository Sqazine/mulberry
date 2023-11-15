#pragma once
#include <cstdint>
#include <tuple>
#include "Math/Color.h"
namespace mulberry
{
    enum class PrimitiveRenderType
    {
        POINT_LIST,
        LINE_LIST,
        LINE_STRIP,
        TRIANGLE_LIST,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };

    enum class CullType
    {
        NONE,
        FRONT,
        BACK,
        FRONT_AND_BACK
    };

    enum class DepthTest
    {
        NONE,
        ALWAYS,
        NEVER,
        LESS,
        EQUAL,
        LESS_EQUAL,
        GREATER,
        NOT_EQUAL,
        GREATER_EQUAL,
    };

    enum class DepthMask
    {
        OPEN,
        CLOSE,
    };

    enum class StencilMask
    {
        OPEN,
        CLOSE,
    };

    enum class BlendFunc
    {
        ZERO,
        ONE,

        SRC_COLOR,
        ONE_MINUS_SRC_COLOR,

        DST_COLOR,
        ONE_MINUS_DST_COLOR,

        SRC_ALPHA,
        ONE_MINUS_SRC_ALPHA,

        DST_ALPHA,
        ONE_MINUS_DST_ALPHA,

        CONSTANT_COLOR,
        ONE_MINUS_CONSTANT_COLOR,

        CONSTANT_ALPHA,
        ONE_MINUS_CONSTANT_ALPHA,

        SRC_ALPHA_SATURATE,

        SRC1_COLOR,
        ONE_MINUS_SRC1_COLOR,

        SRC1_ALPHA,
        ONE_MINUS_SRC1_ALPHA
    };

    struct Viewport
    {
        uint32_t x, y, width, height;
    };

    struct RasterPipelineState
    {
        Viewport viewport;
        PrimitiveRenderType primitiveRenderType;
        CullType cullType;
        DepthTest depthTest;
        DepthMask depthMask;
        StencilMask stencilMask;
        std::tuple<bool, BlendFunc, BlendFunc> blendState;
        uint32_t pointSize;
    };
}