#include "FrameBuffer.h"
#include "GraphicsContext.h"
#include "Utils.h"
#include "Logger.h"
#include "App.h"

namespace mulberry::rhi::vk
{
	FrameBuffer::FrameBuffer(RenderPass* renderPass,Texture *attachment)
		: mExtent(attachment->GetImage()->GetExtent()), mHandle(VK_NULL_HANDLE)
	{
		VkFramebufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.renderPass = renderPass->GetHandle();
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = &attachment->GetImage()->GetView();
		createInfo.width = mExtent.x;
		createInfo.height = mExtent.y;
		createInfo.layers = 1;

		VK_CHECK(vkCreateFramebuffer(mDevice.GetHandle(), &createInfo, nullptr, &mHandle));
	}

	FrameBuffer::~FrameBuffer()
	{
		vkDestroyFramebuffer(VK_DEVICE->GetHandle(),mHandle,nullptr);
	}

	const VkFramebuffer &FrameBuffer::GetHandle() const
	{
		return mHandle;
	}

	const Vec2 &FrameBuffer::GetExtent() const
	{
		return mExtent;
	}
}