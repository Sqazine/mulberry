#include "Instance.h"
#include "Context.h"
#include "Utils.h"
#include <SDL2/SDL.h>
namespace VK
{

    Instance::Instance()
        : m_InstanceHandle(VK_NULL_HANDLE)
    {
        VkApplicationInfo appInfo{
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pNext = nullptr,
            .pApplicationName = nullptr,
            .applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
            .pEngineName = nullptr,
            .engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
            .apiVersion =Context::m_RenderCreateInfo.apiVersion== RENDER_API_NEWEST? VK_HEADER_VERSION_COMPLETE: Context::m_RenderCreateInfo.apiVersion,
        };

        EnumerateLayerProperties();
        EnumerateExtentsionProperties();

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.enabledLayerCount = Context::m_RenderCreateInfo.useValidationLayer ? (uint32_t)m_InstanceLayerProps.size() : 0;
        std::vector<const char *> layerNames;
        if (Context::m_RenderCreateInfo.useValidationLayer)
        {
            for (const auto layerProp : m_InstanceLayerProps)
                layerNames.emplace_back(layerProp.layerName);
            createInfo.ppEnabledLayerNames = layerNames.data();
        }
        else
            createInfo.ppEnabledLayerNames = nullptr;
        createInfo.enabledExtensionCount = m_InstanceExtensionProps.size();
        std::vector<const char *> extensionNames;
        for (const auto &extProp : m_InstanceExtensionProps)
            extensionNames.emplace_back(extProp.extensionName);
        if (Context::m_RenderCreateInfo.useValidationLayer)
            extensionNames.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        createInfo.ppEnabledExtensionNames = extensionNames.data();
        createInfo.pApplicationInfo = &appInfo;
        createInfo.flags = 0;

        VK_CHECK_RESULT(vkCreateInstance(&createInfo, nullptr, &m_InstanceHandle));
    }
    Instance::~Instance()
    {
        vkDestroyInstance(m_InstanceHandle, nullptr);
    }

    bool Instance::IsExtensionSupport(std::string_view extName)
    {
        for (const auto& extProp : m_InstanceExtensionProps)
            if (extProp.extensionName == extName)
                return true;
        return false;
    }

    bool Instance::IsLayerSupport(std::string_view layerName)
    {
        for (const auto& layer : m_InstanceLayerProps)
            if (layer.layerName == layerName)
                return true;
        return false;
    }

    void Instance::EnumerateLayerProperties()
    {
        uint32_t instanceLayerCount;
        vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
        m_InstanceLayerProps.resize(instanceLayerCount);
        vkEnumerateInstanceLayerProperties(&instanceLayerCount, m_InstanceLayerProps.data());
    }

    void Instance::EnumerateExtentsionProperties()
    {
        uint32_t instanceExtensionCount;
        vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, nullptr);
        m_InstanceExtensionProps.resize(instanceExtensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, m_InstanceExtensionProps.data());
    }

    void Instance::PrintInfo()
    {
        SDL_Log("Available vulkan instance layers:\n");
        for (const auto &layerProps : m_InstanceLayerProps)
        {
            SDL_Log("\tname:%s\n\tdesc:%s\n\timplVer:%d.%d.%d\n\tspecVer:%d.%d.%d\n",
                    layerProps.layerName,
                    layerProps.description,
                    VK_VERSION_MAJOR(layerProps.implementationVersion),
                    VK_VERSION_MINOR(layerProps.implementationVersion),
                    VK_VERSION_PATCH(layerProps.implementationVersion),
                    VK_VERSION_MAJOR(layerProps.specVersion),
                    VK_VERSION_MINOR(layerProps.specVersion),
                    VK_VERSION_PATCH(layerProps.specVersion));
        }

        SDL_Log("Available vulkan instance extensions:\n");
        for (const auto &extensionProps : m_InstanceExtensionProps)
        {
            SDL_Log("\tname:%s\n\tspecVer:%d.%d.%d", extensionProps.extensionName,
                    VK_VERSION_MAJOR(extensionProps.specVersion),
                    VK_VERSION_MINOR(extensionProps.specVersion),
                    VK_VERSION_PATCH(extensionProps.specVersion));
        }
    }

}