#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include <SDL2/SDL.h>
#include "Math/Color.h"
namespace mulberry
{
    struct ImgData
    {
        std::vector<uint8_t> pixels{};
        uint32_t width = 0, height = 0, channel = 4;
    };

    enum class WrapMode
    {
        REPEAT,
        MIRROR_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER,
    };

    enum class FilterMode
    {
        NEAREST,
        LINEAR,
        TRILINEAR,
        NEAREST_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_NEAREST
    };

    enum class Format
    {
        R8,
        RG8,
        RGB8,
        RGBA8,

        R16F,
        RG16F,
        RGB16F,
        RGBA16F,

        R32F,
        RG32F,
        RGB32F,
        RGBA32F,
    };

    struct TextureInfo
    {
        WrapMode wrapS = WrapMode::REPEAT;
        WrapMode wrapT = WrapMode::REPEAT;
        FilterMode filterMode = FilterMode::NEAREST;
        Format format = Format::RGBA8;
        Color borderColor = Color::Black;
        ImgData data;
    };

    struct Texture
    {
    public:
        Texture();
        Texture(const TextureInfo &info);
        ~Texture();

        void CreateFrom(const TextureInfo &info);
        void CreateFromSurface(SDL_Surface *surface);

        const TextureInfo &GetCreateInfo() const;

    private:
        friend class ShaderProgram;
        std::unique_ptr<class GLTexture> mGLTexture;
        //std::unique_ptr<class VKTexture> mVKTexture;
    };
}