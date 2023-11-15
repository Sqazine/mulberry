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

    RasterPipeline::RasterPipeline(const RasterPipelineState &config)
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

    void RasterPipeline::SetPSO(const RasterPipelineState &state)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->SetPSO(state);
            break;
        default:
            mVKRasterPipeline->SetPSO(state);
            break;
        }
    }
    const RasterPipelineState &RasterPipeline::GetPSO() const
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetPSO();
            break;
        default:
            return mVKRasterPipeline->GetPSO();
            break;
        }
    }
    RasterPipelineState &RasterPipeline::GetPSO()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLRasterPipeline->GetPSO();
            break;
        default:
            return mVKRasterPipeline->GetPSO();
            break;
        }
    }

    void RasterPipeline::Render(const Primitive &primitive)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->Render(primitive.GetIndexBuffer()->mGLIndexBuffer.get());
            break;
        default:
            mVKRasterPipeline->Render(primitive.GetIndexBuffer()->mVKIndexBuffer.get());
            break;
        }
    }

    void RasterPipeline::RenderInstanced(const Primitive &primitive, uint32_t instanceCount)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLRasterPipeline->RenderInstanced(primitive.GetIndexBuffer()->mGLIndexBuffer.get(), instanceCount);
            break;
        default:
            mVKRasterPipeline->RenderInstanced(primitive.GetIndexBuffer()->mVKIndexBuffer.get(), instanceCount);
            break;
        }
    }
}