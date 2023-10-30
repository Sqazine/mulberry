#include "GLUtils.h"
#include "Graphics/RHI/Shader.h"
#include "Graphics/RHI/RasterPipeline.h"
#include "GL/GLContext.h"
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

    uint32_t ToGLPrimitiveRenderType(PrimitiveRenderType type)
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
// TODO
            break;
        }
        return GL_RGBA;
    }

    uint32_t ToGLBlendFunc(BlendFunc mode)
    {
        switch (mode)
        {
        case BlendFunc::ZERO:
            return GL_ZERO;
        case BlendFunc::ONE:
            return GL_ONE;
        case BlendFunc::SRC_COLOR:
            return GL_SRC_COLOR;
        case BlendFunc::ONE_MINUS_SRC_COLOR:
            return GL_ONE_MINUS_SRC_COLOR;
        case BlendFunc::SRC_ALPHA:
            return GL_SRC_ALPHA;
        case BlendFunc::ONE_MINUS_SRC_ALPHA:
            return GL_ONE_MINUS_SRC_ALPHA;
        case BlendFunc::DST_ALPHA:
            return GL_DST_ALPHA;
        case BlendFunc::ONE_MINUS_DST_ALPHA:
            return GL_ONE_MINUS_DST_ALPHA;
        case BlendFunc::CONSTANT_COLOR:
            return GL_CONSTANT_COLOR;
        case BlendFunc::ONE_MINUS_CONSTANT_COLOR:
            return GL_ONE_MINUS_CONSTANT_COLOR;
        case BlendFunc::CONSTANT_ALPHA:
            return GL_CONSTANT_ALPHA;
        case BlendFunc::ONE_MINUS_CONSTANT_ALPHA:
            return GL_ONE_MINUS_CONSTANT_ALPHA;
        case BlendFunc::SRC_ALPHA_SATURATE:
            return GL_SRC_ALPHA_SATURATE;
        case BlendFunc::SRC1_COLOR:
            return GL_SRC1_COLOR;
        case BlendFunc::ONE_MINUS_SRC1_COLOR:
            return GL_ONE_MINUS_SRC1_COLOR;
        case BlendFunc::SRC1_ALPHA:
            return GL_SRC1_ALPHA;
        case BlendFunc::ONE_MINUS_SRC1_ALPHA:
            return GL_ONE_MINUS_SRC1_ALPHA;
        default:
            return GL_ZERO;
        }
    }

    std::string ToGLShaderSourceCode(std::string_view source)
    {
        auto version = GLContext::GetInstance().GetVersion();
        return "#version " + std::to_string((int32_t)version.x) + std::to_string((int32_t)version.y) + "0 core\n" + std::string(source);
    }

    void ToGLRawPSO(const RasterPipelineState &state)
    {
        glViewport(state.viewport.x, state.viewport.y, state.viewport.width, state.viewport.height);

        glPointSize(state.pointSize);

        switch (state.cullType)
        {
        case CullType::NONE:
            glDisable(GL_CULL_FACE);
            break;
        case CullType::FRONT:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            break;
        case CullType::BACK:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            break;
        case CullType::FRONT_AND_BACK:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT_AND_BACK);
            break;
        default:
            glDisable(GL_CULL_FACE);
            break;
        }

        if (state.depthTest == DepthTest::NONE)
            glDisable(GL_DEPTH_TEST);
        else
            glEnable(GL_DEPTH_TEST);

        switch (state.depthTest)
        {
        case DepthTest::ALWAYS:
            glDepthFunc(GL_ALWAYS);
            break;
        case DepthTest::NEVER:
            glDepthFunc(GL_NEVER);
            break;
        case DepthTest::LESS:
            glDepthFunc(GL_LESS);
            break;
        case DepthTest::EQUAL:
            glDepthFunc(GL_EQUAL);
            break;
        case DepthTest::LESS_EQUAL:
            glDepthFunc(GL_LEQUAL);
            break;
        case DepthTest::GREATER:
            glDepthFunc(GL_GREATER);
            break;
        case DepthTest::NOT_EQUAL:
            glDepthFunc(GL_NOTEQUAL);
            break;
        case DepthTest::GREATER_EQUAL:
            glDepthFunc(GL_GEQUAL);
            break;
        default:
            glDisable(GL_DEPTH_TEST);
            break;
        }

        switch (state.depthMask)
        {
        case DepthMask::OPEN:
            glDepthMask(GL_TRUE);
            break;
        case DepthMask::CLOSE:
        default:
            glDepthMask(GL_FALSE);
            break;
        }

        switch (state.stencilMask)
        {
        case StencilMask::OPEN:
            glStencilMask(GL_TRUE);
            break;
        case StencilMask::CLOSE:
        default:
            glStencilMask(GL_FALSE);
            break;
        }

        if (std::get<0>(state.blendState))
            glEnable(GL_BLEND);
        else
            glDisable(GL_BLEND);

        glBlendFunc(ToGLBlendFunc(std::get<1>(state.blendState)), ToGLBlendFunc(std::get<2>(state.blendState)));
    }

    void ToDefaultGLRawPSO()
    {
        glPointSize(1);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glStencilMask(GL_FALSE);
        glDisable(GL_BLEND);
    }
}