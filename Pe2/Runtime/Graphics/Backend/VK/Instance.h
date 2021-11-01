#pragma once
#include <vulkan/vulkan.h>
#include "../../../Window.h"
namespace VK
{
    const std::vector<const char *> g_ValidationLayers = {
        "VK_LAYER_KHRONOS_validation"};

    class Instance
    {
    public:
        Instance(const Window *windowHandle);
        ~Instance();

        const VkInstance &GetHandle() const;
    private:
        std::vector<const char *> GetRequiredExtensions();

        VkInstance m_InstanceHandle;

        const Window *m_WindowHandle;
    };
}