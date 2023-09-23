#include "Window.h"

namespace mulberry
{
    Window::Window()
        :
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
          mSDL2WindowImpl()
#else
#error "Unknown platform Window"
#endif
    {
    }

    Window::~Window()
    {
    }

    void Window::SetTitle(std::string_view str)
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        mSDL2WindowImpl.SetTitle(str);
#else
#error "Unknown platform Window"
#endif
    }
    std::string_view Window::GetTitle() const
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
       return mSDL2WindowImpl.GetTitle();
#else
#error "Unknown platform Window"
#endif
    }
    void Window::Resize(const Vec2 &extent)
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        mSDL2WindowImpl.Resize(extent);
#else
#error "Unknown platform Window"
#endif
    }
    void Window::Resize(uint32_t w, uint32_t h)
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        mSDL2WindowImpl.Resize(w, h);
#else
#error "Unknown platform Window"
#endif
    }
    Vec2 Window::GetSize()
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        return mSDL2WindowImpl.GetSize();
#else
#error "Unknown platform Window"
#endif
    }

    const Viewport &Window::GetViewport() const
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        return mSDL2WindowImpl.GetViewport();
#else
#error "Unknown platform Window"
#endif
    }

    void Window::Show()
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        mSDL2WindowImpl.Show();
#else
#error "Unknown platform Window"
#endif
    }
    void Window::Hide()
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        mSDL2WindowImpl.Hide();
#else
#error "Unknown platform Window"
#endif
    }

    std::vector<const char *> Window::GetVulkanRequiredExtensions()
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        return mSDL2WindowImpl.GetVulkanRequiredExtensions();
#else
#error "Unknown platform Window"
#endif
    }
    VkSurfaceKHR Window::CreateSurface(VkInstance instance)
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        return mSDL2WindowImpl.CreateSurface(instance);
#else
#error "Unknown platform Window"
#endif
    }
}