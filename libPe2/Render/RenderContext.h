#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include <string_view>
namespace Pe2
{
    enum WindowFlags
    {
        WINDOW_FULLSCREEN = 0x00000001, 
        WINDOW_BORDERLESS = 0x00000010, 
        WINDOW_RESIZABLE = 0x00000020,  
        WINDOW_FULLSCREEN_DESKTOP = (WINDOW_FULLSCREEN | 0x00001000),
    };

    struct WindowInfo
    {
        std::string title;
        float width;
        float height;
        int32_t flags=0;
    };

    enum RenderFlags
    {
        RENDER_DBUFFER = 0x00000001,
        RENDER_VSYNC = 0x00000010,

    };
    struct RenderContextInfo
    {
        WindowInfo windowInfo;
        uint32_t flags = RENDER_DBUFFER | RENDER_VSYNC;
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