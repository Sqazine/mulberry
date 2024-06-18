#pragma once
#include <vulkan/vulkan.h>
#include "Defs.h"
#include "Device.h"
#include "Format.h"

namespace mulberry::vk
{
    class RenderPass:public Base
    {
    public:
        RenderPass(Format colorformat);
        ~RenderPass();

        const VkRenderPass& GetHandle() const;

    private:
        VkRenderPass mRenderPass;
    };
}