
#pragma once
#include <memory>
#include "Instance.h"
#include "Device.h"
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "../RenderContextInfo.h"
namespace Pe2::VK
{
    class Context
    {
    public:
        static void Init(const RenderContextInfo &config);
        static void Destroy();

        static Device *GetDevice();
        static Instance *GetInstance();
        static SDL_Window *GetWindow();

    private:
        Context() {}
        static std::unique_ptr<Instance> m_Instance;
        static std::unique_ptr<Device> m_Device;

        static SDL_Window *m_WindowHandle;
    };
}