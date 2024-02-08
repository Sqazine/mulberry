#pragma once
#include <vulkan/vulkan.h>
#include "Device.h"
#include "../Format.h"
#include "../Enum.h"
#include "Object.h"

namespace mulberry::rhi::vk
{
    class RenderPass:public Object
    {
    public:
        RenderPass(Format colorformat);
        ~RenderPass();

        const VkRenderPass& GetHandle() const;

    private:
        VkRenderPass mRenderPass;
    };
}