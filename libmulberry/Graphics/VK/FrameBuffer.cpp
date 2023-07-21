#include "FrameBuffer.h"
#include "Context.h"
#include "Utils.h"
#include "Logger.h"

namespace mulberry::vk
{

	FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, const RenderPass* renderPass, const std::vector<const ImageView*>& attachments)
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

		VK_CHECK(vkCreateFramebuffer(Context::GetInstance().GetDevice()->GetHandle(), &createInfo, nullptr, &mFrameBuffer));
	}

	FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, const RenderPass* renderPass, const std::vector<VkImageView>& attachments)
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

		VK_CHECK(vkCreateFramebuffer(Context::GetInstance().GetDevice()->GetHandle(), &createInfo, nullptr, &mFrameBuffer));
	}

	FrameBuffer::~FrameBuffer()
	{
		vkDestroyFramebuffer(Context::GetInstance().GetDevice()->GetHandle(), mFrameBuffer, nullptr);
	}

	const VkFramebuffer& FrameBuffer::GetHandle() const
	{
		return mFrameBuffer;
	}

}