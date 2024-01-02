#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include <SDL.h>
#include "Math/Color.h"
#include "Math/Vec2.h"
#include "Core/AssetManager.h"
#include "Format.h"
#include "Enum.h"
#include "Graphics/RHI/VK/Texture.h"

namespace mulberry
{
    struct Texture
    {
    public:
        Texture();
        ~Texture();

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;

        Vec2 GetExtent() const;
    private:
        friend class RasterShaderGroup;
        friend class RasterPass;
        std::unique_ptr<vk::Texture> mVKTextureImpl;
    };
}