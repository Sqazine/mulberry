#include "VKFrameBuffer.h"
#include "VKContext.h"
#include "VKUtils.h"
#include "Logger.h"
#include "App.h"

namespace mulberry
{
	VKFrameBuffer::VKFrameBuffer(uint32_t width, uint32_t height, const VKRenderPass *renderPass, const std::vector<const VKTexture *> &attachments)
	{
		std::vector<VkImageView> attachmentsView(attachments.size());

		for (int i = 0; i < attachmentsView.size(); ++i)
			attachmentsView[i] = attachments[i]->GetView()->GetHandle();

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

		VK_CHECK(vkCreateFramebuffer(RAW_VK_DEVICE_HANDLE, &createInfo, nullptr, &mFrameBuffer));
	}


	VKFrameBuffer::~VKFrameBuffer()
	{
		vkDestroyFramebuffer(RAW_VK_DEVICE_HANDLE, mFrameBuffer, nullptr);
	}

	const VkFramebuffer &VKFrameBuffer::GetHandle() const
	{
		return mFrameBuffer;
	}

}