#pragma once
#include <vulkan/vulkan.h>
#include "Core/AssetManager.h"
#include "Math/Color.h"
#include "../Format.h"
#include "Image.h"
#include "Sampler.h"

namespace mulberry::vk
{
    class Texture
    {
    public:
        Texture();
        Texture(VkImage rawImage, Format format);
        ~Texture();

        const Image *GetImage() const;

        VkDescriptorImageInfo ToVkDescriptorImageInfo() const;
    private:
        std::unique_ptr<Image> mImage;
        std::unique_ptr<Sampler> mSampler;
    };
}