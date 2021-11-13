#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include <string_view>
#include "RHI/RenderContextCreateInfo.h"
namespace GL
{
    class Context
    {
    public:
        ~Context();

        static void CreateContext(const RenderContextCreateInfo &config);

        static void InitContext(SDL_Window *window);
        static void DestroyContext();

        static bool IsSupportExtension(std::string_view extensionName);

        static void SwapWindow();

        static SDL_GLContext GetContextHandle();

    private:
        Context();

        static RenderContextCreateInfo m_RenderCreateInfo;

        static SDL_GLContext m_ContextHandle;

        static SDL_Window *m_WindowHandle;
    };
}