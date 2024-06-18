#pragma once
#include <memory>
#include <vulkan/vulkan.h>
#include "Math/Vec2.h"
#include "Core/AssetManager.h"
#include "Color.h"
#include "Graphics/RHI/Format.h"
#include "Sampler.h"

namespace mulberry::vk
{
    class Texture
    {
    public:
        Texture();
        Texture(const Vec2 &extent, VkImage rawImage, Format format);
        ~Texture();

        void SetImageData(const ImageData &data);

        class Image *GetImage();
        Sampler *GetSampler();

        VkDescriptorImageInfo ToVkDescriptorImageInfo() const;

    private:
        std::unique_ptr<class Image> mImage;
        std::unique_ptr<Sampler> mSampler;
    };
}