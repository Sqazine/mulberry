#pragma once
#include <vulkan/vulkan.h>
#include "Device.h"

namespace mulberry::vk 
{
    class RenderPass
    {
    public:
        RenderPass(const std::vector<VkFormat>& colorformats, VkFormat depthFormat);
        ~RenderPass();

        const VkRenderPass& GetHandle() const;

    private:
        VkRenderPass mRenderPass;
    };
}