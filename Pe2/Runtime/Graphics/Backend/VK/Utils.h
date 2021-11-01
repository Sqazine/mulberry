#pragma once
#include <vector>
#include <vulkan/vulkan.h>
namespace VK
{
#define VK_CHECK(x)                                                                                                                 \
    do                                                                                                                              \
    {                                                                                                                               \
        VkResult err = x;                                                                                                           \
        if (err)                                                                                                                    \
        {                                                                                                                           \
            std::cout << "Vulkan error: " << err << "in file:" << __FILE__ << ",in line:" << std::to_string(__LINE__) << std::endl; \
            abort();                                                                                                                \
        }                                                                                                                           \
    } while (0);

    std::vector<VkLayerProperties> GetInstanceLayerProps();
    std::vector<VkExtensionProperties> GetInstanceExtensionProps();
    bool CheckValidationLayerSupport(std::vector<const char *> validationLayerNames, std::vector<VkLayerProperties> instanceLayerProps);
    bool CheckExtensionSupport(std::vector<const char *> extensionNames, std::vector<VkExtensionProperties> extensionProps);
}
