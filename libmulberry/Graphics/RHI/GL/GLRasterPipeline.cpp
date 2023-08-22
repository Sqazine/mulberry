#include "GLRasterPipeline.h"
#include <unordered_map>
#include "Graphics/Primitive.h"
#include "GL/GLUtils.h"
namespace mulberry
{
    GLRasterPipeline::GLRasterPipeline()
    {
    }

    GLRasterPipeline::GLRasterPipeline(const RasterPipelineConfig &config)
        : mConfig(config)
    {
    }

    GLRasterPipeline::~GLRasterPipeline()
    {
    }

    void GLRasterPipeline::SetBufferClearColor(const Color &color)
    {
        mConfig.clearColor = color;
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void GLRasterPipeline::ClearColorBuffer()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    Viewport GLRasterPipeline::GetViewport() const
    {
        std::array<int32_t, 4> v;
        glGetIntegerv(GL_VIEWPORT, v.data());
        Viewport result;
        result.x = v[0];
        result.y = v[1];
        result.width = v[2];
        result.height = v[3];

        return result;
    }

    void GLRasterPipeline::SetViewport(const Viewport &info)
    {
        mConfig.viewport = info;
        glViewport(info.x, info.y, info.width, info.height);
    }

    void GLRasterPipeline::SetPointSize(uint32_t size)
    {
        mConfig.pointSize = size;
        glPointSize(size);
    }

    uint32_t GLRasterPipeline::GetPointSize() const
    {
        return mConfig.pointSize;
    }

    void GLRasterPipeline::SetCull(CullType cullType)
    {
        mConfig.cullType = cullType;

        switch (mConfig.cullType)
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
    }
    const CullType &GLRasterPipeline::GetCullType() const
    {
        return mConfig.cullType;
    }

    void GLRasterPipeline::SetDepthTest(DepthTestType depthTest)
    {
        mConfig.depthTestType = depthTest;

        if (mConfig.depthTestType == DepthTestType::NONE)
            glDisable(GL_DEPTH_TEST);
        else
            glEnable(GL_DEPTH_TEST);

        switch (mConfig.depthTestType)
        {
        case DepthTestType::ALWAYS:
            glDepthFunc(GL_ALWAYS);
            break;
        case DepthTestType::NEVER:
            glDepthFunc(GL_NEVER);
            break;
        case DepthTestType::LESS:
            glDepthFunc(GL_LESS);
            break;
        case DepthTestType::EQUAL:
            glDepthFunc(GL_EQUAL);
            break;
        case DepthTestType::LESS_EQUAL:
            glDepthFunc(GL_LEQUAL);
            break;
        case DepthTestType::GREATER:
            glDepthFunc(GL_GREATER);
            break;
        case DepthTestType::NOT_EQUAL:
            glDepthFunc(GL_NOTEQUAL);
            break;
        case DepthTestType::GREATER_EQUAL:
            glDepthFunc(GL_GEQUAL);
            break;
        default:
            glDisable(GL_DEPTH_TEST);
            break;
        }
    }
    const DepthTestType &GLRasterPipeline::GetDepthTest() const
    {
        return mConfig.depthTestType;
    }

    void GLRasterPipeline::SetDepthMask(DepthMask depthMask)
    {
        mConfig.depthMask = depthMask;

        switch (mConfig.depthMask)
        {
        case DepthMask::OPEN:
            glDepthMask(GL_TRUE);
            break;
        case DepthMask::CLOSE:
        default:
            glDepthMask(GL_FALSE);
            break;
        }
    }

    const DepthMask &GLRasterPipeline::GetDepthMask() const
    {
        return mConfig.depthMask;
    }

    void GLRasterPipeline::SetStencilMask(StencilMask stencilMask)
    {
        mConfig.stencilMask = stencilMask;
        switch (mConfig.stencilMask)
        {
        case StencilMask::OPEN:

            glStencilMask(GL_TRUE);
            break;
        case StencilMask::CLOSE:
        default:
            glStencilMask(GL_FALSE);
            break;
        }
    }
    const StencilMask &GLRasterPipeline::GetStencilMask() const
    {
        return mConfig.stencilMask;
    }

    void GLRasterPipeline::SetBlendState(bool isOpen, BlendFunc srcFunc, BlendFunc dstFunc)
    {
        mConfig.blendState = {isOpen, srcFunc, dstFunc};

        if (isOpen)
            glEnable(GL_BLEND);
        else
            glDisable(GL_BLEND);

        glBlendFunc(ToGLBlendFunc(srcFunc), ToGLBlendFunc(dstFunc));
    }
    std::tuple<bool, BlendFunc, BlendFunc> GLRasterPipeline::GetBlendState() const
    {
        return mConfig.blendState;
    }

    void GLRasterPipeline::Render(const GLIndexBuffer *ibo, PrimitiveRenderType mode)
    {
        glEnable(GL_MULTISAMPLE);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->GetHandle());
        glDrawElements(ToGLPrimitiveType(mode), ibo->Size(), ibo->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void GLRasterPipeline::RenderInstanced(const GLIndexBuffer *ibo, PrimitiveRenderType mode, uint32_t instanceCount)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->GetHandle());
        glDrawElementsInstanced(ToGLPrimitiveType(mode), ibo->Size(), ibo->GetDataType(), nullptr, instanceCount);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}