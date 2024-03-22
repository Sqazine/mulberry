#pragma once
#include <cstdint>
#include <type_traits>
#include "Utils/Utils.h"
namespace mulberry::rhi
{
    enum class ShaderStage : uint64_t
    {
        VERTEX = 1,
        FRAGMENT = 2,
        GEOMETRY = 4,
        TESSELLATION_CONTROL = 8,
        TESSELLATION_EVALUATION = 16,
        COMPUTE = 32,
        ALL_GRAPHICS = VERTEX | FRAGMENT | GEOMETRY | TESSELLATION_CONTROL | TESSELLATION_EVALUATION,
        ALL = ALL_GRAPHICS | COMPUTE,
    };

#define RHI_SHADER_STAGE_CAST(shaderStage) (static_cast<uint64_t>(std::underlying_type<ShaderStage>::type(shaderStage)))
    ENUM_CLASS_OP(RHI_SHADER_STAGE_CAST, ShaderStage, uint64_t);

    enum class SampleCount
    {
        X1,
        X2,
        X4,
        X8,
        X16,
        X32,
        X64,
    };

    enum class FrontFace
    {
        CW,
        CCW,
    };

    enum class CullMode
    {
        NONE,
        FRONT,
        BACK,
        BOTH
    };

    enum class FilterMode
    {
        NEAREST,
        LINEAR
    };

    enum class WrapMode
    {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER,
    };

    enum class PrimitiveTopology
    {
        POINT_LIST,
        LINE_LIST,
        LINE_STRIP,
        TRIANGLE_LIST,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,

        LINE_LIST_WITH_ADJACENCY,
        LINE_STRIP_WITH_ADJACENCY,
        TRIANGLE_LIST_WITH_ADJACENCY,
        TRIANGLE_STRIP_WITH_ADJACENCY,
    };

    enum class PolygonMode
    {
        FILL,
        LINE,
        POINT,
    };

    enum class MipMapMode
    {
        NEAREST,
        LINEAR
    };

    enum class BorderColor
    {
        FLOAT_TRANSPARENT_BLACK,
        INT_TRANSPARENT_BLACK,

        FLOAT_OPAQUE_BLACK,
        INT_OPAQUE_BLACK,

        FLOAT_OPAQUE_WHITE,
        INT_OPAQUE_WHITE,
    };

    enum class BlendFactor
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
        ONE_MINUS_SRC1_ALPHA,
    };

    enum class CompareOp : uint64_t
    {
        NEVER,
        LESS,
        EQUAL,
        LESS_OR_EQUAL,
        GREATER,
        NOT_EQUAL,
        GREATER_OR_EQUAL,
        ALWAYS,
    };

    enum class AttachmentLoad
    {
        LOAD,
        CLEAR,
        DONT_CARE,
    };

    enum class AttachmentStore
    {
        STORE,
        DONT_CARE,
    };
}