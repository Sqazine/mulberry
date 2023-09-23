#include "Window.h"
#include "App.h"
#include "WindowImpl.h"
namespace mulberry
{
    WindowImpl::WindowImpl()
        : mHandle(nullptr), mIsShown(false)
    {
        auto flag = SDL_Init(SDL_INIT_EVERYTHING);
        if (flag < 0)
            MULBERRY_CORE_ERROR("Failed to init sdl2");

        SDL_Rect rect;
        auto ret = SDL_GetDisplayBounds(0, &rect);

        uint32_t windowFlag = SDL_WINDOW_HIDDEN|SDL_WINDOW_ALLOW_HIGHDPI;

        if (App::GetInstance().GetGraphicsConfig().backend == GraphicsBackend::GL)
            windowFlag |= SDL_WINDOW_OPENGL;
        else
            windowFlag |= SDL_WINDOW_VULKAN;

        mHandle = SDL_CreateWindow(mTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, rect.w / 4, rect.h / 4, windowFlag);

        mViewport = Viewport{
            .x = 0,
            .y = 0,
            .width = (uint32_t)rect.w / 4,
            .height = (uint32_t)rect.h / 4,
        };
    }

    WindowImpl::~WindowImpl()
    {
        if (mHandle)
            SDL_DestroyWindow(mHandle);
    }

    void WindowImpl::SetTitle(std::string_view str)
    {
        mTitle = str;
        SDL_SetWindowTitle(mHandle, mTitle.c_str());
    }

    std::string_view WindowImpl::GetTitle() const
    {
        return SDL_GetWindowTitle(mHandle);
    }

    void WindowImpl::Resize(const Vec2 &extent)
    {
        Resize(extent.x, extent.y);
    }

    void WindowImpl::Resize(uint32_t w, uint32_t h)
    {
        mViewport = {0, 0, w, h};
        SDL_SetWindowSize(mHandle, w, h);
        SDL_SetWindowPosition(mHandle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }

    Vec2 WindowImpl::GetSize()
    {
        int32_t x, y;
        SDL_GetWindowSize(mHandle, (int *)&x, (int *)&y);
        return Vec2(x, y);
    }

    SDL_Window *WindowImpl::GetHandle()
    {
        return mHandle;
    }

    const Viewport &WindowImpl::GetViewport() const
    {
        return mViewport;
    }

    void WindowImpl::Show()
    {
        SDL_ShowWindow(mHandle);
        mIsShown = true;
    }
    void WindowImpl::Hide()
    {
        SDL_HideWindow(mHandle);
        mIsShown = false;
    }

    std::vector<const char *> WindowImpl::GetVulkanRequiredExtensions()
    {
        uint32_t extensionCount;
        SDL_Vulkan_GetInstanceExtensions(mHandle, &extensionCount, nullptr);
        std::vector<const char *> result(extensionCount);
        SDL_Vulkan_GetInstanceExtensions(mHandle, &extensionCount, result.data());
        return result;
    }

    VkSurfaceKHR WindowImpl::CreateSurface(VkInstance instance)
    {
        VkSurfaceKHR result = VK_NULL_HANDLE;
        SDL_bool flag = SDL_Vulkan_CreateSurface(mHandle, instance, &result);
        if (flag == SDL_FALSE)
            MULBERRY_CORE_ERROR("Failed to create vulkan surface from window.");
        return result;
    }

}