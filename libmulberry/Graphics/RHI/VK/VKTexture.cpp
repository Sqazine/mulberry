#include "VKTexture.h"

namespace mulberry
{
    VKTexture::VKTexture()
    {
    }
    VKTexture::VKTexture(const TextureInfo &info)
    :mInfo(info)
    {
    }
    VKTexture::~VKTexture()
    {
    }

    void VKTexture::CreateFrom(const TextureInfo &info)
    {
    }
    void VKTexture::CreateFromSurface(SDL_Surface *surface)
    {
    }

    uint32_t VKTexture::GetHandle() const
    {
    }
    const TextureInfo &VKTexture::GetCreateInfo() const
    {
        return mInfo;
    }
}