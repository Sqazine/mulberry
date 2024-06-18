#include "Texture.h"
#include "Logger.h"
#include "Graphics/RHI/VK/Image.h"
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

    void Texture::SetImageData(const ImageData &data)
    {
        mImage=std::make_unique<Image>(data.width,data.height,data.format,ImageTiling::LINEAR,ImageUsage::SAMPLED|ImageUsage::TRANSFER_DST,MemoryProperty::DEVICE_LOCAL);
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