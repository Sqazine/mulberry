#pragma once
#include <cstdint>
#include <SDL2/SDL.h>
#include <memory>
#include <vulkan/vulkan.h>
#include "../RenderContextCreateInfo.h"
namespace VK
{
    class Context
    {
    public:
       static void CreateContext(const RenderContextCreateInfo &config);

        ~Context();

        static void InitContext(SDL_Window *window);
        static void DestroyContext();

    private:
        Context();

        static RenderContextCreateInfo m_RenderCreateInfo;

        friend class Instance;
        friend class DebugMessenger;
        friend class PhysicalDeviceList;
        friend class PhysicalDevice;
        friend class LogicalDevice;
        friend class Surface;
        friend class SwapChain;
        friend class ShaderModule;

        static std::unique_ptr<class Instance> m_Instance;
        static std::unique_ptr<class DebugMessenger> m_DebugMessenger;
        static std::unique_ptr<class Surface> m_Surface;
        static std::unique_ptr<class PhysicalDeviceList> m_PhysicalDeviceList;
        static std::unique_ptr<class LogicalDevice> m_LogicalDevice;
        static std::unique_ptr<class SwapChain> m_SwapChain;

        static SDL_Window *m_WindowHandle;
    };
}