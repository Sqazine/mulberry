#pragma once
#include <memory>
#include <vulkan/vulkan.h>
#include "Math/Vec2.h"
#include "Core/AssetManager.h"
#include "Graphics/Color.h"
#include "Graphics/RHI/Format.h"
#include "Graphics/RHI/Texture.h"
#include "Sampler.h"
#include "Image.h"
namespace mulberry::vk
{
    class Texture : public mulberry::Texture
    {
    public:
        Texture();
        ~Texture() override;

        Texture *SetImageData(const ImageData &data) override;
        Texture *SetMagFilter(FilterMode filter) override;
        Texture *SetMinFilter(FilterMode filter) override;
        Texture *SetWrapU(WrapMode address) override;
        Texture *SetWrapV(WrapMode address) override;
        Texture *SetWrapW(WrapMode address) override;
        Texture *SetAnisotropyLevel(float level) override;
        Texture *SetBorderColor(BorderColor borderColor) override;
        Texture *SetMipMapMode(MipMapMode mipmapMode) override;
        Texture *SetMipMapBias(float bias) override;
        Texture *SetMinMipMapLevel(float level) override;
        Texture *SetMaxMipMapLevel(float level) override;

        FilterMode GetMagFilter() const override;
        FilterMode GetMinFilter() const override;
        WrapMode GetWrapModeU() const override;
        WrapMode GetWrapModeV() const override;
        WrapMode GetWrapModeW() const override;
        float GetMaxAnisotropyLevel() const override;
        BorderColor GetBorderColor() const override;
        MipMapMode GetMipMapMode() const override;
        float GetMipMapBias() const override;
        float GetMinMipMapLevel() const override;
        float GetMaxMipMapLevel() const override;

        Vec2 GetExtent() const override;

        Image *GetImage() const;
        Sampler *GetSampler() const;

        VkDescriptorImageInfo ToVkDescriptorImageInfo() const;

    private:
        friend class SwapChain;
        Texture(const Vec2 &extent, VkImage rawImage, Format format);
        std::unique_ptr<Image> mImage{nullptr};
        std::unique_ptr<Sampler> mSampler{nullptr};
    };
}