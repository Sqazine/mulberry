#include "Texture.h"
#include "Logger.h"
namespace mulberry::vk
{
    Texture::Texture()
        : mSampler(std::make_unique<Sampler>())
    {
    }

    Texture::Texture(const Vec2 &extent, VkImage rawImage, Format format)
        : mImage(std::make_unique<Image>(extent, rawImage, format)), mSampler(std::make_unique<Sampler>())
    {
    }

    Texture::~Texture()
    {
        mSampler.reset(nullptr);
        mImage.reset(nullptr);
    }

    Texture* Texture::SetImageData(const ImageData &data)
    {
        mImage=std::make_unique<Image>(data.width,data.height,data.format,ImageTiling::LINEAR,ImageUsage::SAMPLED|ImageUsage::TRANSFER_DST,MemoryProperty::DEVICE_LOCAL);
        return this;
    }

    Texture* Texture::SetMagFilter(FilterMode filter)
    {
        GetSampler()->SetMagFilter(filter);
        return this;
    }

    Texture* Texture::SetMinFilter(FilterMode filter)
    {
        GetSampler()->SetMinFilter(filter);
        return this;
    }

    Texture* Texture::SetWrapU(WrapMode address)
    {
        GetSampler()->SetWrapU(address);
        return this;
    }

    Texture* Texture::SetWrapV(WrapMode address)
    {
        GetSampler()->SetWrapV(address);
        return this;
    }

    Texture* Texture::SetWrapW(WrapMode address)
    {
        GetSampler()->SetWrapW(address);
        return this;
    }

    Texture* Texture::SetAnisotropyLevel(float level)
    {
        GetSampler()->SetAnisotropyLevel(level);
        return this;
    }

    Texture* Texture::SetBorderColor(BorderColor borderColor)
    {
        GetSampler()->SetBorderColor(borderColor);
        return this;
    }

    Texture* Texture::SetMipMapMode(MipMapMode mipmapMode)
    {
        GetSampler()->SetMipMapMode(mipmapMode);
        return this;
    }

    Texture* Texture::SetMipMapBias(float bias)
    {
        GetSampler()->SetMipMapBias(bias);
        return this;
    }

    Texture* Texture::SetMinMipMapLevel(float level)
    {
        GetSampler()->SetMinMipMapLevel(level);
        return this;
    }

    Texture* Texture::SetMaxMipMapLevel(float level)
    {
        GetSampler()->SetMaxMipMapLevel(level);
        return this;
    }

    FilterMode Texture::GetMagFilter() const
    {
       return GetSampler()->GetMagFilter();
    }

    FilterMode Texture::GetMinFilter() const
    {
        return GetSampler()->GetMinFilter();
    }

    WrapMode Texture::GetWrapModeU() const
    {
        return GetSampler()->GetWrapModeU();
    }

    WrapMode Texture::GetWrapModeV() const
    {
        return GetSampler()->GetWrapModeV();
    }

    WrapMode Texture::GetWrapModeW() const
    {
        return GetSampler()->GetWrapModeW();
    }

    float Texture::GetMaxAnisotropyLevel() const
    {
        return GetSampler()->GetMaxAnisotropyLevel();
    }

    BorderColor Texture::GetBorderColor() const
    {
        return GetSampler()->GetBorderColor();
    }

    MipMapMode Texture::GetMipMapMode() const
    {
        return GetSampler()->GetMipMapMode();
    }

    float Texture::GetMipMapBias() const
    {
        return GetSampler()->GetMipMapBias();
    }

    float Texture::GetMinMipMapLevel() const
    {
        return GetSampler()->GetMinMipMapLevel();
    }

    float Texture::GetMaxMipMapLevel() const
    {
        return GetSampler()->GetMaxMipMapLevel();
    }

    Vec2 Texture::GetExtent() const
    {
        return GetImage()->GetExtent();
    }

    Image *Texture::GetImage() const
    {
        return mImage.get();
    }

    Sampler *Texture::GetSampler() const
    {
        return mSampler.get();
    }

    VkDescriptorImageInfo Texture::ToVkDescriptorImageInfo() const
    {
        VkDescriptorImageInfo result;
        result.sampler = mSampler->GetHandle();
        result.imageView = mImage->GetView();
        result.imageLayout = IMAGE_LAYOUT_CAST(mImage->GetImageLayout());
        return result;
    }
}