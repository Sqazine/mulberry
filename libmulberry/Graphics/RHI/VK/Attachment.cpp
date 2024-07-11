#include "Attachment.h"
#include "Texture.h"

namespace mulberry::vk
{
    const VkAttachmentDescription &ColorAttachment::GetVkAttachmentDescription()
    {
        auto vkImpl = dynamic_cast<vk::Texture *>(this->GetTexture());
        mDesc = {};
        mDesc.flags = 0;
        mDesc.format = ToVkFormat(vkImpl->GetImage()->GetFormat());
        mDesc.samples = VK_SAMPLE_COUNT_1_BIT;
        mDesc.loadOp = ToLoadOp(GetLoadOp());
        mDesc.storeOp = ToStoreOp(GetStoreOp());
        mDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        mDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        mDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        mDesc.finalLayout = VkImageLayout(VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL | VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

        return mDesc;
    }

    VkClearValue ColorAttachment::GetVkClearValue()
    {
        VkClearValue result{};
        result.color.float32[0] = this->mClearColor.r;
        result.color.float32[1] = this->mClearColor.g;
        result.color.float32[2] = this->mClearColor.b;
        result.color.float32[3] = this->mClearColor.a;
        return result;
    }
}