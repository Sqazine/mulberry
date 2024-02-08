#include "Texture.h"
#include "Logger.h"
#include "Texture.h"
namespace mulberry::rhi::vk
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
    }

    void Texture::SetImageData(const ImageData &data)
    {
        // mImage->
    }

    Image *Texture::GetImage()
    {
        return mImage.get();
    }

    Sampler *Texture::GetSampler()
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