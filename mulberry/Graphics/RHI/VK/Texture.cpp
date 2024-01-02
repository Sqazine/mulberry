#include "Texture.h"
#include "Logger.h"
namespace mulberry::vk
{
    Texture::Texture()
    {
    }

    Texture::Texture(VkImage rawImage, Format format)
        : mImage(std::make_unique<Image>(rawImage, format))
    {
    }

    Texture::~Texture()
    {
    }
    
    const Image *Texture::GetImage() const
    {
        return mImage.get();
    }
    
    VkDescriptorImageInfo Texture::ToVkDescriptorImageInfo() const
    {
		VkDescriptorImageInfo result;
		result.sampler = mSampler->GetHandle();
		result.imageView = mImage->GetView();
		result.imageLayout = IMAGE_LAYOUT_CAST( mImage->GetImageLayout());
		return result;
    }
}