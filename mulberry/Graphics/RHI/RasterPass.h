// #pragma once
// #include <memory>
// #include "Math/Color.h"
// #include "Graphics/RHI/GL/GLRasterPass.h"
// #include "Graphics/RHI/VK/VKRasterPass.h"
// namespace mulberry
// {
//     class RasterPass
//     {
//     public:
//         RasterPass(const Vec2 &extent, Format format, uint32_t imageCount);
//         ~RasterPass();

//         void SetClearColor(const Color &clearColor);
//         void IsClearColorBuffer(bool isClear);

//         void Begin();
//         void End();

//     private:
//         std::unique_ptr<GLRasterPass> mGLRasterPass;
//         std::unique_ptr<VKRasterPass> mVKRasterPass;
//     };
// }