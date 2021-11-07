#pragma once
#include <vulkan/vulkan.h>


namespace VK
{
    class Surface 
    {
    public:
        Surface();
        ~Surface();

    private:
        friend class Context;
        friend class PhysicalDeviceList;
        friend class SwapChain;

        VkSurfaceKHR m_SurfaceHandle;
    };
}