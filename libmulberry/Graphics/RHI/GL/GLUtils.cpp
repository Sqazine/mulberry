#include "GLUtils.h"
#include "Graphics/RHI/Shader.h"
#include "Graphics/RHI/RasterPipeline.h"
#include <unordered_map>
namespace mulberry
{
    uint32_t ToGLShaderType(ShaderType type)
    {
        const std::unordered_map<ShaderType, uint32_t> maps = {
            {ShaderType::VERTEX, GL_VERTEX_SHADER},
            {ShaderType::FRAGMENT, GL_FRAGMENT_SHADER},
            {ShaderType::GEOMETRY, GL_GEOMETRY_SHADER},
            {ShaderType::TESSELLATION_CONTROL, GL_TESS_CONTROL_SHADER},
            {ShaderType::TESSELLATION_EVAL, GL_TESS_EVALUATION_SHADER},
            {ShaderType::COMPUTE, GL_COMPUTE_SHADER},
        };

        return maps.find(type)->second;
    }

    uint32_t ToGLPrimitiveType(PrimitiveRenderType type)
    {
        const std::unordered_map<PrimitiveRenderType, uint32_t> maps = {
            {PrimitiveRenderType::POINT_LIST, GL_POINTS},
            {PrimitiveRenderType::LINE_LIST, GL_LINES},
            {PrimitiveRenderType::LINE_STRIP, GL_LINE_STRIP},
            {PrimitiveRenderType::TRIANGLE_LIST, GL_TRIANGLES},
            {PrimitiveRenderType::TRIANGLE_STRIP, GL_TRIANGLE_STRIP},
            {PrimitiveRenderType::TRIANGLE_FAN, GL_TRIANGLE_FAN},
        };

        return maps.find(type)->second;
    }

    uint32_t ToGLWarpMode(WrapMode mode)
    {
        switch (mode)
        {
        case WrapMode::REPEAT:
            return GL_REPEAT;
        case WrapMode::MIRROR_REPEAT:
            return GL_MIRRORED_REPEAT;
        case WrapMode::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case WrapMode::CLAMP_TO_BORDER:
            return GL_CLAMP_TO_BORDER;
        default:
            return GL_REPEAT;
        }
    }
    uint32_t ToGLFilterMode(FilterMode mode)
    {
        switch (mode)
        {
        case FilterMode::NEAREST:
            return GL_NEAREST;
        case FilterMode::LINEAR:
            return GL_LINEAR;
        case FilterMode::TRILINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        case FilterMode::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        case FilterMode::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case FilterMode::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        default:
            return GL_NEAREST;
        }
    }

    uint32_t ToGLFormat(Format mode)
    {
        switch (mode)
        {
        case Format::R8:
            return GL_R8;
        case Format::RG8:
            return GL_RG8;
        case Format::RGB8:
            return GL_RGB8;
        case Format::RGBA8:
            return GL_RGBA8;
        case Format::R16F:
            return GL_R16F;
        case Format::RG16F:
            return GL_RG16;
        case Format::RGB16F:
            return GL_RGB16F;
        case Format::R32F:
            return GL_R32F;
        case Format::RG32F:
            return GL_RG32F;
        case Format::RGB32F:
            return GL_RGB32F;
        case Format::RGBA32F:
            return GL_RGBA32F;
        default:
            break;
        }
        return GL_RGBA;
    }
}