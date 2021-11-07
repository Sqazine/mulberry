#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string_view>

namespace VK
{

    class Instance
    {
    public:
        Instance();
        ~Instance();

        bool IsExtensionSupport(std::string_view extName);
        bool IsLayerSupport(std::string_view layerName);

    private:
        void EnumerateLayerProperties();
        void EnumerateExtentsionProperties();

        friend class Context;
        friend class DebugMessenger;
        friend class PhysicalDeviceList;
        friend class PhysicalDevice;
        friend class Surface;

        void PrintInfo();

        VkInstance m_InstanceHandle;

        std::vector<VkLayerProperties> m_InstanceLayerProps;
        std::vector<VkExtensionProperties> m_InstanceExtensionProps;
    };
}