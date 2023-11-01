#pragma once
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
        VKTexture(const TextureInfo &info);
        ~VKTexture();

        void CreateFrom(const TextureInfo &info);
        void CreateFromSurface(SDL_Surface *surface);

        uint32_t GetHandle() const;
        const TextureInfo &GetCreateInfo() const;

    private:
        std::unique_ptr<VKImage> mImage;
        std::unique_ptr<VKImageView> mImageView;

        TextureInfo mInfo;
    };
}