#include "FrameBuffer.h"
#include "Context.h"
#include "Utils.h"
#include "Logger.h"

namespace mulberry::vk
{
	FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, const RenderPass *renderPass,const Texture * attachments)
		:mHandle(VK_NULL_HANDLE)
	{
		VkFramebufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.renderPass = renderPass->GetHandle();
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = &attachments->GetImage()->GetView();
		createInfo.width = width;
		createInfo.height = height;
		createInfo.layers = 1;

		VK_CHECK(vkCreateFramebuffer(mDevice.GetHandle(), &createInfo, nullptr, &mHandle));
	}


	FrameBuffer::~FrameBuffer()
	{
		vkDestroyFramebuffer(mDevice.GetHandle(), mHandle, nullptr);
	}

	const VkFramebuffer &FrameBuffer::GetHandle() const
	{
		return mHandle;
	}

}