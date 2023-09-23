#pragma once
#include <vulkan/vulkan.h>
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include "SDL2Wrapper/SDL2Window.h"
#else
#endif

namespace mulberry
{
    class Window
    {
    public:
        Window();
        ~Window();

        void SetTitle(std::string_view str);
        std::string_view GetTitle() const;
        void Resize(const Vec2 &extent);
        void Resize(uint32_t w, uint32_t h);
        Vec2 GetSize();

        const Viewport &GetViewport() const;

        void Show();
        void Hide();

    private:
        friend class VKAdapter;
        std::vector<const char *> GetVulkanRequiredExtensions();
        VkSurfaceKHR CreateSurface(VkInstance instance);

    private:
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        friend class SDL2GlContext;
        SDL2Window mSDL2WindowImpl;
#else
#error "Unknown platform Window"
#endif
    };
}