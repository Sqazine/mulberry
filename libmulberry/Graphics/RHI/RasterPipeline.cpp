#include "RasterPipeline.h"
#include "App.h"
#include "GL/GLRasterPipeline.h"
#include "VK/VKRasterPipeline.h"
namespace mulberry
{
    RasterPipeline::RasterPipeline()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline = std::make_unique<GLRasterPipeline>();
            break;
        default:
            mVKRasterPipeline = std::make_unique<VKRasterPipeline>();
            break;
        }
    }

    RasterPipeline::RasterPipeline(const RasterPipelineConfig &config)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline = std::make_unique<GLRasterPipeline>(config);
            break;
        default:
            mVKRasterPipeline = std::make_unique<VKRasterPipeline>(config);
            break;
        }
    }

    RasterPipeline::~RasterPipeline()
    {
    }

    void RasterPipeline::SetBufferClearColor(const Color &color)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetBufferClearColor(color);
            break;
        default:
            mVKRasterPipeline->SetBufferClearColor(color);
            break;
        }
    }

    void RasterPipeline::ClearColorBuffer()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->ClearColorBuffer();
            break;
        default:
            mVKRasterPipeline->ClearColorBuffer();
            break;
        }
    }

    Viewport RasterPipeline::GetViewport()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetViewport();
        default:
            return mVKRasterPipeline->GetViewport();
            break;
        }
    }

    void RasterPipeline::SetViewport(const Viewport &info)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetViewport(info);
            break;
        default:
            mGLRasterPipeline->SetViewport(info);
            break;
        }
    }

    void RasterPipeline::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        SetViewport(Viewport{
            .x = x,
            .y = y,
            .width = width,
            .height = height});
    }

    void RasterPipeline::Render(const Primitive &primitive, PrimitiveRenderType mode)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->Render(primitive.GetIndexBuffer()->mGLIndexBuffer.get(), mode);
            break;
        default:
            mVKRasterPipeline->Render(primitive.GetIndexBuffer()->mVKIndexBuffer.get(), mode);
            break;
        }
    }

    void RasterPipeline::RenderInstanced(const Primitive &primitive, PrimitiveRenderType mode, uint32_t instanceCount)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->RenderInstanced(primitive.GetIndexBuffer()->mGLIndexBuffer.get(), mode, instanceCount);
            break;
        default:
            mVKRasterPipeline->RenderInstanced(primitive.GetIndexBuffer()->mVKIndexBuffer.get(), mode, instanceCount);
            break;
        }
    }

    void RasterPipeline::SetPointSize(uint32_t size)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetPointSize(size);
            break;
        default:
            mVKRasterPipeline->SetPointSize(size);
            break;
        }
    }

    uint32_t RasterPipeline::GetPointSize() const
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetPointSize();
        default:
            return mVKRasterPipeline->GetPointSize();
        }
    }

    void RasterPipeline::SetCull(CullType cullType)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetCull(cullType);
            break;
        default:
            mVKRasterPipeline->SetCull(cullType);
            break;
        }
    }

    const CullType &RasterPipeline::GetCull() const
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetCullType();
        default:
            return mVKRasterPipeline->GetCullType();
        }
    }

    void RasterPipeline::SetDepthTest(DepthTestType depthTest)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetDepthTest(depthTest);
            break;
        default:
            mVKRasterPipeline->SetDepthTest(depthTest);
            break;
        }
    }

    const DepthTestType &RasterPipeline::GetDepthTest() const
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetDepthTest();
        default:
            return mVKRasterPipeline->GetDepthTest();
        }
    }

    void RasterPipeline::SetDepthMask(DepthMask depthMask)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetDepthMask(depthMask);
            break;
        default:
            mVKRasterPipeline->SetDepthMask(depthMask);
            break;
        }
    }

    const DepthMask &RasterPipeline::GetDepthMask() const
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetDepthMask();
        default:
            return mVKRasterPipeline->GetDepthMask();
        }
    }

    void RasterPipeline::SetStencilMask(StencilMask stencilMask)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetStencilMask(stencilMask);
            break;
        default:
            mVKRasterPipeline->SetStencilMask(stencilMask);
            break;
        }
    }
    const StencilMask &RasterPipeline::GetStencilMask() const
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetStencilMask();
        default:
            return mVKRasterPipeline->GetStencilMask();
        }
    }

    void RasterPipeline::SetBlendState(bool isOpen, BlendFunc srcFunc, BlendFunc dstFunc)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetBlendState(isOpen, srcFunc, dstFunc);
            break;
        default:
            mVKRasterPipeline->SetBlendState(isOpen, srcFunc, dstFunc);
            break;
        }
    }
    std::tuple<bool, BlendFunc, BlendFunc> RasterPipeline::GetBlendState() const
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetBlendState();
        default:
            return mVKRasterPipeline->GetBlendState();
        }
    }
}