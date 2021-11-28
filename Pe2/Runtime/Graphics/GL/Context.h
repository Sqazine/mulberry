#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include <string_view>
#include "../RenderContextInfo.h"
namespace Pe2::GL
{
    class Context
    {
    public:
        ~Context();

        static void Init(const RenderContextInfo &config);
        static void Destroy();

        static bool IsSupportExtension(std::string_view extensionName);

        static void SwapWindow();

        static SDL_GLContext GetContextHandle();

        static SDL_Window *GetWindow();

    private:
        Context();

        static RenderContextInfo m_RenderCreateInfo;

        static SDL_GLContext m_ContextHandle;

        static SDL_Window *m_WindowHandle;
    };
}