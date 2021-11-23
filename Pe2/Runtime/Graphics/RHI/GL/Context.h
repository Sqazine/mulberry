#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include <string_view>
#include "../RenderContextCreateInfo.h"
namespace GL
{
    class Context
    {
    public:
        ~Context();

        static void CreateContext(const RenderContextCreateInfo &config);
        static void DestroyContext();

        static bool IsSupportExtension(std::string_view extensionName);

        static void SwapWindow();

        static SDL_GLContext GetContextHandle();

        static SDL_Window *GetWindowHandle();

    private:
        Context();

        static RenderContextCreateInfo m_RenderCreateInfo;

        static SDL_GLContext m_ContextHandle;

        static SDL_Window *m_WindowHandle;
    };
}