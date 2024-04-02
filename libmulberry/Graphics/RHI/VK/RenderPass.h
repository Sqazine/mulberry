#pragma once
#include <vulkan/vulkan.h>
#include "Device.h"
#include "Format.h"
#include "Enum.h"
#include "Base.h"

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