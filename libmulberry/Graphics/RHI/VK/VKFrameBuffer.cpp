#include "VKFrameBuffer.h"
#include "VKContext.h"
#include "VKUtils.h"
#include "Logger.h"

namespace mulberry
{
	VKFrameBuffer::VKFrameBuffer(uint32_t width, uint32_t height, const VKRenderPass *renderPass, const std::vector<const VKImageView *> &attachments)
	{
		std::vector<VkImageView> attachmentsView(attachments.size());

		for (int i = 0; i < attachmentsView.size(); ++i)
			attachmentsView[i] = attachments[i]->GetHandle();

		VkFramebufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.renderPass = renderPass->GetHandle();
		createInfo.attachmentCount = attachmentsView.size();
		createInfo.pAttachments = attachmentsView.data();
		createInfo.width = width;
		createInfo.height = height;
		createInfo.layers = 1;

		VK_CHECK(vkCreateFramebuffer(VKContext::GetInstance().GetDevice()->GetHandle(), &createInfo, nullptr, &mFrameBuffer));
	}

	VKFrameBuffer::VKFrameBuffer(uint32_t width, uint32_t height, const VKRenderPass *renderPass, const std::vector<VkImageView> &attachments)
	{
		VkFramebufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.renderPass = renderPass->GetHandle();
		createInfo.attachmentCount = attachments.size();
		createInfo.pAttachments = attachments.data();
		createInfo.width = width;
		createInfo.height = height;
		createInfo.layers = 1;

		VK_CHECK(vkCreateFramebuffer(VKContext::GetInstance().GetDevice()->GetHandle(), &createInfo, nullptr, &mFrameBuffer));
	}

	VKFrameBuffer::~VKFrameBuffer()
	{
		vkDestroyFramebuffer(VKContext::GetInstance().GetDevice()->GetHandle(), mFrameBuffer, nullptr);
	}

	const VkFramebuffer &VKFrameBuffer::GetHandle() const
	{
		return mFrameBuffer;
	}

}