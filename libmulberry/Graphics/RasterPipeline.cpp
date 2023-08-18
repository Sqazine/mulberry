#include "RasterPipeline.h"
#include "App.h"
#include "GL/GLRasterPipeline.h"
namespace mulberry
{
    RasterPipeline::RasterPipeline()
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline = std::make_unique<GLRasterPipeline>();
            break;
        default:
            //TODO...
            break;
        }
    }
    RasterPipeline::RasterPipeline(const RasterPipelineConfig &config)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline = std::make_unique<GLRasterPipeline>(config);
            break;
        default:
            //TODO...
            break;
        }
    }
    RasterPipeline::~RasterPipeline()
    {
    }

    void RasterPipeline::SetBufferClearColor(const Color &color)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetBufferClearColor(color);
            break;
        default:
            //TODO...
            break;
        }
    }

    void RasterPipeline::ClearColorBuffer()
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->ClearColorBuffer();
            break;
        default:
            //TODO...
            break;
        }
    }
    Viewport RasterPipeline::GetViewport()
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetViewport();
        default:
            //TODO...
            break;
        }
    }
    void RasterPipeline::SetViewport(const Viewport &info)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetViewport(info);
            break;
        default:
            //TODO...
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
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->Render(primitive.GetIndexBuffer(), mode);
            break;
        default:
            //TODO...
            break;
        }
    }
    void RasterPipeline::RenderInstanced(const Primitive &primitive, PrimitiveRenderType mode, uint32_t instanceCount)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->RenderInstanced(primitive.GetIndexBuffer(), mode, instanceCount);
            break;
        default:
            //TODO...
            break;
        }
    }

    void RasterPipeline::SetPointSize(uint32_t size)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetPointSize(size);
            break;
        default:
            //TODO...
            break;
        }
    }
    uint32_t RasterPipeline::GetPointSize() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetPointSize();
        default:
            //TODO...
            break;
        }
    }

    void RasterPipeline::SetCull(CullType cullType)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetCull(cullType);
        default:
            //TODO...
            break;
        }
    }
    const CullType &RasterPipeline::GetCull() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetCullType();
        default:
            //TODO...
            break;
        }
    }

    void RasterPipeline::SetDepthTest(DepthTestType depthTest)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetDepthTest(depthTest);
        default:
            //TODO...
            break;
        }
    }
    const DepthTestType &RasterPipeline::GetDepthTest() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetDepthTest();
        default:
            //TODO...
            break;
        }
    }

    void RasterPipeline::SetDepthMask(DepthMask depthMask)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetDepthMask(depthMask);
        default:
            //TODO...
            break;
        }
    }
    const DepthMask &RasterPipeline::GetDepthMask() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetDepthMask();
        default:
            //TODO...
            break;
        }
    }

}