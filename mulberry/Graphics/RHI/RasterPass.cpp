// #include "RasterPass.h"
// #include "App.h"
// namespace mulberry
// {
//     RasterPass::RasterPass(const Vec2 &extent, Format format, uint32_t imageCount)
//     {
//         switch (AppConfig::graphicsConfig.backend)
//         {
//         case GraphicsBackend::GL:
//             mGLRasterPass = std::make_unique<GLRasterPass>();
//             break;
//         default:
//             mVKRasterPass = std::make_unique<VKRasterPass>(extent, format, imageCount);
//             break;
//         }
//     }

//     RasterPass::~RasterPass()
//     {
//     }

//     void RasterPass::SetClearColor(const Color &clearColor)
//     {
//         switch (AppConfig::graphicsConfig.backend)
//         {
//         case GraphicsBackend::GL:
//             mGLRasterPass->SetClearColor(clearColor);
//             break;
//         default:
//             mVKRasterPass->SetClearColor(clearColor);
//             break;
//         }
//     }
//     void RasterPass::IsClearColorBuffer(bool isClear)
//     {
//         switch (AppConfig::graphicsConfig.backend)
//         {
//         case GraphicsBackend::GL:
//             mGLRasterPass->IsClearColorBuffer(isClear);
//             break;
//         default:
//             mVKRasterPass->IsClearColorBuffer(isClear);
//             break;
//         }
//     }

//     void RasterPass::Begin()
//     {
//         switch (AppConfig::graphicsConfig.backend)
//         {
//         case GraphicsBackend::GL:
//             mGLRasterPass->Begin();
//             break;
//         default:
//             mVKRasterPass->Begin();
//             break;
//         }
//     }
//     void RasterPass::End()
//     {
//         switch (AppConfig::graphicsConfig.backend)
//         {
//         case GraphicsBackend::GL:
//             mGLRasterPass->End();
//             break;
//         default:
//             mVKRasterPass->End();
//             break;
//         }
//     }
// }