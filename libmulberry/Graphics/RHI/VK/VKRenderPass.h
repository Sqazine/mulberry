#pragma once
#include <vulkan/vulkan.h>
#include "VKDevice.h"

namespace mulberry 
{
    class VKRenderPass
    {
    public:
        VKRenderPass(const std::vector<VkFormat>& colorformats);
        ~VKRenderPass();

        const VkRenderPass& GetHandle() const;

    private:
        VkRenderPass mRenderPass;
    };
}