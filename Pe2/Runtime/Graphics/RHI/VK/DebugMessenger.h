#pragma once
#include <vulkan/vulkan.h>

namespace VK
{
    class DebugMessenger 
    {
    public:
        DebugMessenger();
        ~DebugMessenger();

    private:
        friend class Context;

        VkDebugUtilsMessengerEXT m_DebugMessengerHandle;
    };
}