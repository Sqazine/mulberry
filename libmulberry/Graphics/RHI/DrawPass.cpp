#include "DrawPass.h"
#include "App.h"
namespace mulberry
{
    DrawPass::DrawPass()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLDrawPass = std::make_unique<GLDrawPass>();
            break;
        default:
            // TODO
            break;
        }
    }

    DrawPass::~DrawPass()
    {
    }

    void DrawPass::SetClearColor(const Color &clearColor)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLDrawPass->SetClearColor(clearColor);
            break;
        default:
            // TODO
            break;
        }
    }
    void DrawPass::IsClearColorBuffer(bool isClear)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLDrawPass->IsClearColorBuffer(isClear);
            break;
        default:
            // TODO
            break;
        }
    }

    void DrawPass::Begin()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLDrawPass->Begin();
            break;
        default:
            // TODO
            break;
        }
    }
    void DrawPass::End()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLDrawPass->End();
            break;
        default:
            // TODO
            break;
        }
    }
}