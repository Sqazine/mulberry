#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include "Core/AssetManager.h"
#include "Color.h"
#include "RHI/Format.h"
#include "Image.h"
#include "Sampler.h"

namespace mulberry::rhi::vk
{
    class Texture
    {
    public:
        Texture();
        ~Texture();

        void SetImageData(const ImageData& data);

        Image *GetImage() ;
        Sampler* GetSampler();

        VkDescriptorImageInfo ToVkDescriptorImageInfo() const;
    private:
        friend class SwapChain;
        Texture(const Vec2& extent, VkImage rawImage, Format format);
        std::unique_ptr<Image> mImage;
        std::unique_ptr<Sampler> mSampler;
    };
}