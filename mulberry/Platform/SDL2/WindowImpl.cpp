#include "Window.h"
#include "App.h"
#include "WindowImpl.h"
#include "Graphics/Viewport.h"
namespace mulberry
{
    SDL2WindowImpl::SDL2WindowImpl()
        : mHandle(nullptr), mIsShown(false),
          mIsWindowCloseButtonClick(false),
          mIsWindowMaxButtonClick(false),
          mIsWindowMinButtonClick(false),
          mTitle("mulberry")
    {
        auto flag = SDL_Init(SDL_INIT_EVERYTHING);
        if (flag < 0)
            MULBERRY_CORE_ERROR("Failed to init sdl2");

        SDL_Rect rect;
        auto ret = SDL_GetDisplayBounds(0, &rect);

        uint32_t windowFlag = SDL_WINDOW_HIDDEN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE;

        if (App::GetInstance().GetGraphicsConfig().backend == GraphicsBackend::VK)
            windowFlag |= SDL_WINDOW_VULKAN;
        else
            windowFlag |= SDL_WINDOW_OPENGL;

        mHandle = SDL_CreateWindow(mTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, rect.w * 0.75, rect.h * 0.75, windowFlag);

        mViewport = Viewport(0, 0,(uint32_t)rect.w * 0.75, (uint32_t)rect.w * 0.75);
    }

    SDL2WindowImpl::~SDL2WindowImpl()
    {
        if (mHandle)
            SDL_DestroyWindow(mHandle);
        SDL_Quit();
    }

    void SDL2WindowImpl::SetTitle(std::string_view str)
    {
        mTitle = str;
        SDL_SetWindowTitle(mHandle, mTitle.c_str());
    }

    std::string_view SDL2WindowImpl::GetTitle() const
    {
        return SDL_GetWindowTitle(mHandle);
    }

    void SDL2WindowImpl::Resize(const Vec2 &extent)
    {
        Resize(static_cast<uint32_t>(extent.x), static_cast<uint32_t>(extent.y));
    }

    void SDL2WindowImpl::Resize(uint32_t w, uint32_t h)
    {
        mViewport = Viewport(0, 0, w, h);
        SDL_SetWindowSize(mHandle, w, h);
        SDL_SetWindowPosition(mHandle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        mIsWindowResize = true;
    }

    Vec2 SDL2WindowImpl::GetSize()
    {
        int32_t x, y;
        SDL_GetWindowSize(mHandle, &x, &y);
        return Vec2(static_cast<float>(x), static_cast<float>(y));
    }

    SDL_Window *SDL2WindowImpl::GetHandle()
    {
        return mHandle;
    }

    const Viewport &SDL2WindowImpl::GetViewport() const
    {
        return mViewport;
    }

    void SDL2WindowImpl::Show()
    {
        SDL_ShowWindow(mHandle);
        mIsShown = true;
    }
    void SDL2WindowImpl::Hide()
    {
        SDL_HideWindow(mHandle);
        mIsShown = false;
    }

    std::vector<const char *> SDL2WindowImpl::GetVulkanRequiredExtensions()
    {
        uint32_t extensionCount;
        SDL_Vulkan_GetInstanceExtensions(mHandle, &extensionCount, nullptr);
        std::vector<const char *> result(extensionCount);
        SDL_Vulkan_GetInstanceExtensions(mHandle, &extensionCount, result.data());
        return result;
    }

    VkSurfaceKHR SDL2WindowImpl::CreateSurface(VkInstance instance)
    {
        VkSurfaceKHR result = VK_NULL_HANDLE;
        SDL_bool flag = SDL_Vulkan_CreateSurface(mHandle, instance, &result);
        if (flag == SDL_FALSE)
            MULBERRY_CORE_ERROR("Failed to create vulkan surface from window.");
        return result;
    }

    void SDL2WindowImpl::PreUpdate()
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            mIsWindowCloseButtonClick = true;
            break;
        case SDL_WINDOWEVENT:
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_MINIMIZED:
                mIsWindowMinButtonClick = true;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                mIsWindowMaxButtonClick = true;
                break;
            case SDL_WINDOWEVENT_CLOSE:
                mIsWindowCloseButtonClick = true;
                break;
            case SDL_WINDOWEVENT_RESIZED:
                mIsWindowResize = true;
            default:
                break;
            }
        }
        default:
            break;
        }
    }

    void SDL2WindowImpl::PostUpdate()
    {
        mIsWindowCloseButtonClick = false;
        mIsWindowMaxButtonClick = false;
        mIsWindowMinButtonClick = false;
        mIsWindowResize = false;
    }

    bool SDL2WindowImpl::IsWindowCloseButtonClick() const
    {
        return mIsWindowCloseButtonClick;
    }

    bool SDL2WindowImpl::IsWindowMaxButtonClick() const
    {
        return mIsWindowMaxButtonClick;
    }

    bool SDL2WindowImpl::IsWindowMinButtonClick() const
    {
        return mIsWindowMinButtonClick;
    }

    bool SDL2WindowImpl::IsResize() const
    {
        return mIsWindowResize;
    }
}