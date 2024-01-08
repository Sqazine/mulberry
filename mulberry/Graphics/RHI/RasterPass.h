#pragma once
#include <memory>
#include <vector>
#include "Math/Color.h"
#include "Graphics/RHI/VK/RasterPass.h"
#include "Texture.h"
namespace mulberry
{
    class RasterPass
    {
    public:
        RasterPass(Format format, const std::vector<Texture*>& textureLists);
        ~RasterPass();

        void SetClearColor(const Color &clearColor);
        void IsClearColorBuffer(bool isClear);

        void Begin();
        void End();

    private:
        std::unique_ptr<vk::RasterPass> mVKRasterPassImpl;
    };
}