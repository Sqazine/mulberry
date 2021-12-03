#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include <string_view>
namespace Pe2
{
    enum class RenderBackend
    {
        GL,
        VK,
    };

    enum RenderFlag
    {
        DOUBLE_BUFFERING = 1,
        VSYNC = 2
    };

    struct WindowInfo
    {
        std::string title;
        float width;
        float height;
        bool resizeable = true;
        bool fullScreen = false;
    };

    struct RenderContextInfo
    {
        WindowInfo windowInfo;
        RenderBackend backend = RenderBackend::GL;
        int flag = DOUBLE_BUFFERING | VSYNC;
    };

    class RenderContext
    {
    public:
        ~RenderContext();

        static void Init(const RenderContextInfo &config);
        static void Destroy();

        static bool IsSupportExtension(std::string_view extensionName);

        static void SwapWindow();

        static SDL_GLContext GetRenderContextHandle();

        static SDL_Window *GetWindow();

    private:
        RenderContext();

        static RenderContextInfo m_RenderCreateInfo;

        static SDL_GLContext m_RenderContextHandle;

        static SDL_Window *m_WindowHandle;
    };
}