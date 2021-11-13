#include "Context.h"
#include "Instance.h"
#include "DebugMessenger.h"
#include "Device.h"
#include "Surface.h"
#include "SwapChain.h"
#include <iostream>

namespace VK
{
    RenderContextCreateInfo Context::m_RenderCreateInfo;
    std::unique_ptr<Instance> Context::m_Instance;
    std::unique_ptr<DebugMessenger> Context::m_DebugMessenger;
    std::unique_ptr<Surface> Context::m_Surface;
    std::unique_ptr<PhysicalDeviceList> Context::m_PhysicalDeviceList;
    std::unique_ptr<LogicalDevice> Context::m_LogicalDevice;
    std::unique_ptr<SwapChain> Context::m_SwapChain;

    SDL_Window *Context::m_WindowHandle = nullptr;

    Context::Context()
    {
    }

    Context::~Context()
    {
    }

    void Context::CreateContext(const RenderContextCreateInfo &config)
    {
        m_RenderCreateInfo = config;
    }

    void Context::InitContext(SDL_Window *window)
    {
        m_WindowHandle = window;

        m_Instance = std::make_unique<Instance>();

        if (m_RenderCreateInfo.useValidationLayer)
            m_Instance->PrintInfo();

        m_DebugMessenger = nullptr;
        if (m_RenderCreateInfo.useValidationLayer)
            m_DebugMessenger = std::make_unique<DebugMessenger>();

        if (m_RenderCreateInfo.useSurface)
            m_Surface = std::make_unique<Surface>();

        m_PhysicalDeviceList = std::make_unique<PhysicalDeviceList>();

        m_LogicalDevice = std::make_unique<LogicalDevice>();

        m_SwapChain = std::make_unique<SwapChain>();
    }
    void Context::DestroyContext()
    {
    }
}