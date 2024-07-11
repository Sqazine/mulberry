#pragma once
#include <vulkan/vulkan.h>
#include "Graphics/RHI/Attachment.h"
namespace mulberry::vk
{
    class ColorAttachment : public mulberry::ColorAttachment
    {
    public:
        ColorAttachment() = default;
        ~ColorAttachment() override = default;

        const VkAttachmentDescription &GetVkAttachmentDescription();
        VkClearValue GetVkClearValue();
    private:
        VkAttachmentDescription mDesc;
    };
}