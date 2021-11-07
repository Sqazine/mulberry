#include "DebugMessenger.h"
#include "Context.h"
#include "Instance.h"
#include <SDL2/SDL.h>
#include <string>
#include "Utils.h"
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                    void *pUserData)
{
    std::string tags;

    switch (messageSeverity)
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        tags += "[ERROR]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        tags += "[WARN]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        tags += "[INFO]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        tags += "[VERBOSE]";
        break;
    default:
        break;
    }

    switch (messageType)
    {
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
        tags += "[GENERAL]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
        tags += "[VALIDATION]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
        tags += "[PERFORMANCE]";
        break;
    default:
        break;
    }

    switch (pCallbackData->pObjects->objectType)
    {
    case VK_OBJECT_TYPE_INSTANCE:
        tags += "[INSTANCE]";
        break;
    case VK_OBJECT_TYPE_PHYSICAL_DEVICE:
        tags += "[PHYSICAL_DEVICE]";
        break;
    case VK_OBJECT_TYPE_DEVICE:
        tags += "[DEVICE]";
        break;
    case VK_OBJECT_TYPE_QUEUE:
        tags += "[QUEUE]";
        break;
    case VK_OBJECT_TYPE_SEMAPHORE:
        tags += "[SEMAPHORE]";
        break;
    case VK_OBJECT_TYPE_COMMAND_BUFFER:
        tags += "[COMMAND_BUFFER]";
        break;
    case VK_OBJECT_TYPE_FENCE:
        tags += "[FENCE]";
        break;
    case VK_OBJECT_TYPE_DEVICE_MEMORY:
        tags += "[DEVICE_MEMORY]";
        break;
    case VK_OBJECT_TYPE_BUFFER:
        tags += "[BUFFER]";
        break;
    case VK_OBJECT_TYPE_IMAGE:
        tags += "[IMAGE]";
        break;
    case VK_OBJECT_TYPE_EVENT:
        tags += "[EVENT]";
        break;
    case VK_OBJECT_TYPE_QUERY_POOL:
        tags += "[QUERY_POOL]";
        break;
    case VK_OBJECT_TYPE_BUFFER_VIEW:
        tags += "[BUFFER_VIEW]";
        break;
    case VK_OBJECT_TYPE_IMAGE_VIEW:
        tags += "[IMAGE_VIEW]";
        break;
    case VK_OBJECT_TYPE_SHADER_MODULE:
        tags += "[SHADER_MODULE]";
        break;
    case VK_OBJECT_TYPE_PIPELINE_CACHE:
        tags += "[PIPELINE_CACHE]";
        break;
    case VK_OBJECT_TYPE_PIPELINE_LAYOUT:
        tags += "[PIPELINE_LAYOUT]";
        break;
    case VK_OBJECT_TYPE_RENDER_PASS:
        tags += "[RENDER_PASS]";
        break;
    case VK_OBJECT_TYPE_PIPELINE:
        tags += "[PIPELINE]";
        break;
    case VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT:
        tags += "[DESCRIPTOR_SET_LAYOUT]";
        break;
    case VK_OBJECT_TYPE_SAMPLER:
        tags += "[SAMPLER]";
        break;
    case VK_OBJECT_TYPE_DESCRIPTOR_POOL:
        tags += "[DESCRIPTOR_POOL]";
        break;
    case VK_OBJECT_TYPE_DESCRIPTOR_SET:
        tags += "[DESCRIPTOR_SET]";
        break;
    case VK_OBJECT_TYPE_FRAMEBUFFER:
        tags += "[FRAMEBUFFER]";
        break;
    case VK_OBJECT_TYPE_COMMAND_POOL:
        tags += "[COMMAND_POOL]";
        break;
    case VK_OBJECT_TYPE_SURFACE_KHR:
        tags += "[SURFACE_KHR]";
        break;
    case VK_OBJECT_TYPE_SWAPCHAIN_KHR:
        tags += "[SWAPCHAIN_KHR]";
        break;
    case VK_OBJECT_TYPE_DISPLAY_KHR:
        tags += "[DISPLAY_KHR]";
        break;
    case VK_OBJECT_TYPE_DISPLAY_MODE_KHR:
        tags += "[DISPLAY_MODE_KHR]";
        break;
    default:
        break;
    }

    SDL_Log("%s:%s\n", tags.c_str(), pCallbackData->pMessage);

    return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator,
                                      VkDebugUtilsMessengerEXT *pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func)
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks *pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func)
        func(instance, debugMessenger, pAllocator);
}

namespace VK
{

    DebugMessenger::DebugMessenger()
        : m_DebugMessengerHandle(VK_NULL_HANDLE)
    {
        VkDebugUtilsMessengerCreateInfoEXT createInfo =
            {
                .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
                .pNext = nullptr,
                .flags = 0,
                .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
                .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
                .pfnUserCallback = DebugCallback,
                .pUserData = nullptr,
            };

        VK_CHECK_RESULT(CreateDebugUtilsMessengerEXT(Context::m_Instance.get()->m_InstanceHandle, &createInfo, nullptr, &m_DebugMessengerHandle));
    }
    DebugMessenger::~DebugMessenger()
    {
        DestroyDebugUtilsMessengerEXT(Context::m_Instance.get()->m_InstanceHandle, m_DebugMessengerHandle, nullptr);
    }

}