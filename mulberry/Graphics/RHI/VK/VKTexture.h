#pragma once
#include <vulkan/vulkan.h>
#include "Texture.h"
#include "Math/Color.h"
#include "VKImage.h"
#include "VKImageView.h"
namespace mulberry
{
    class VKTexture
    {
    public:
        VKTexture();
        VKTexture(VkImage rawImage, VkFormat format);
        VKTexture(const TextureInfo &info);
        ~VKTexture();

        void CreateFrom(const TextureInfo &info);
        void CreateFromSurface(SDL_Surface *surface);

        const VKImage *GetHandle() const;
        const VKImageView *GetView() const;
        const TextureInfo &GetCreateInfo() const;

    private:
        VkFilter ToVkFilter(FilterMode mode);
        VkSamplerAddressMode ToVkWrapMode(WrapMode mode);

        std::unique_ptr<VKImage> mImage;
        std::unique_ptr<VKImageView> mImageView;

        VkSampler mSampler{VK_NULL_HANDLE};

        TextureInfo mInfo;
    };
}