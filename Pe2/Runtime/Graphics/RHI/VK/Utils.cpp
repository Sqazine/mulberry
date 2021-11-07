#include "Utils.h"

#include <SDL2/SDL_vulkan.h>

namespace VK
{
    std::vector<const char *> GetSDLRequiredExtensions(SDL_Window *window)
    {
        uint32_t extensionCount;
        SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);

        std::vector<const char *> result;
        SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, result.data());
        return result;
    }
}