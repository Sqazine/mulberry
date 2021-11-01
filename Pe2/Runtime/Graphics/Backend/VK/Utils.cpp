#include "Utils.h"
#include <iostream>
namespace VK
{
    std::vector<VkLayerProperties> GetInstanceLayerProps()
    {
        uint32_t availableLayerCount;
        vkEnumerateInstanceLayerProperties(&availableLayerCount, nullptr);
        std::vector<VkLayerProperties> availableInstanceLayerProps(availableLayerCount);
        vkEnumerateInstanceLayerProperties(&availableLayerCount, availableInstanceLayerProps.data());
        return availableInstanceLayerProps;
    }
    std::vector<VkExtensionProperties> GetInstanceExtensionProps()
    {
        uint32_t availableInstanceExtCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &availableInstanceExtCount, nullptr);
        std::vector<VkExtensionProperties> availableInstanceExtProps(availableInstanceExtCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &availableInstanceExtCount, availableInstanceExtProps.data());
        return availableInstanceExtProps;
    }

    bool CheckValidationLayerSupport(std::vector<const char *> validationLayerNames, std::vector<VkLayerProperties> instanceLayerProps)
    {
        for (const char *layerName : validationLayerNames)
        {
            bool layerFound = false;
            for (const auto &layerProperties : instanceLayerProps)
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }

            if (layerFound == false)
                return false;
        }
        return true;
    }

    bool CheckExtensionSupport(std::vector<const char *> extensionNames, std::vector<VkExtensionProperties> extensionProps)
    {
        for (const auto &extName : extensionNames)
        {
            bool extFound = false;
            for (const auto &extProp : extensionProps)
                if (strcmp(extName, extProp.extensionName) == 0)
                {
                    extFound = true;
                    break;
                    ;
                }
            if (extFound = false)
                return false;
        }

        return true;
    }
}