#include "Texture.h"
#include "App.h"
#include "Logger.h"
#include "Graphics/RHI/VK/Texture.h"

namespace mulberry
{
    Texture* Texture::Create()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return new vk::Texture());
    }
    std::unique_ptr<Texture> Texture::CreateUnique()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return std::move(std::make_unique<vk::Texture>()));
    }
}