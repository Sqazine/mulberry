#include "Instance.h"
#include <SDL2/SDL_vulkan.h>
#include "Utils.h"
namespace VK
{
    Instance::Instance(const Window *windowHandle)
        : m_WindowHandle(windowHandle)
    {

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pNext = nullptr;
        appInfo.pApplicationName = nullptr;
        appInfo.applicationVersion = VK_API_VERSION_1_0;
        appInfo.pEngineName = "Pe2";
        appInfo.engineVersion = VK_API_VERSION_1_0;
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo instanceInfo{};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pNext = nullptr;
        instanceInfo.flags = 0;
        instanceInfo.pApplicationInfo = &appInfo;

        auto requiredExts = GetRequiredExtensions();
#ifdef _DEBUG
        requiedExts.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
        if (CheckExtensionSupport(requiredExts, GetInstanceExtensionProps()))
        {
            instanceInfo.enabledExtensionCount = requiredExts.size();
            instanceInfo.ppEnabledExtensionNames = requiredExts.data();
        }
        else
        {
            instanceInfo.enabledExtensionCount = 0;
            instanceInfo.ppEnabledExtensionNames = nullptr;
        }

#if _DEBUG
        instanceInfo.enabledLayerCount = g_ValidationLayers.size();
        instanceInfo.ppEnabledLayerNames = g_ValidationLayers.data();
        if (!CheckValidationLayerSupport(g_ValidationLayers, GetInstanceLayerProps()))
            std::cout << "Lack of necessary validation layer" << std::endl;
#endif
        VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &m_InstanceHandle));
    }
    Instance::~Instance()
    {
        if (m_InstanceHandle != VK_NULL_HANDLE)
        {
            vkDestroyInstance(m_InstanceHandle, nullptr);
            m_InstanceHandle = VK_NULL_HANDLE;
        }
    }

    const VkInstance &Instance::GetHandle() const
    {
        return m_InstanceHandle;
    }

    std::vector<const char *> Instance::GetRequiredExtensions()
    {
        int requiredExtCount;
        SDL_Vulkan_GetInstanceExtensions(m_WindowHandle->GetHandle(), &requiredExtCount, nullptr);
        std::vector<const char *> extNames(requiredExtCount);
        SDL_Vulkan_GetInstanceExtensions(m_WindowHandle->GetHandle(), &requiredExtCount, &extNames.data());
        return extNames;
    }
}