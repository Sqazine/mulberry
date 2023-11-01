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
            mVKDrawPass = std::make_unique<VKDrawPass>();
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
            mVKDrawPass->SetClearColor(clearColor);
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
            mVKDrawPass->IsClearColorBuffer(isClear);
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
            mVKDrawPass->Begin();
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
            mVKDrawPass->End();
            break;
        }
    }
}