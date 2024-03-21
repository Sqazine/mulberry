#include "FrameBuffer.h"
#include "GraphicsContext.h"
#include "Utils.h"
#include "Logger.h"
#include "App.h"

namespace mulberry::rhi::vk
{
	FrameBuffer::FrameBuffer()
		: mHandle(VK_NULL_HANDLE), mInfo({})
	{
		mInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		mInfo.pNext = nullptr;
		mInfo.flags = 0;
		mInfo.layers = 1;
	}

	FrameBuffer::~FrameBuffer()
	{
		if (mHandle)
			vkDestroyFramebuffer(VK_DEVICE->GetHandle(), mHandle, nullptr);
	}

	FrameBuffer &FrameBuffer::AttachRenderPass(RenderPass *renderPass)
	{
		mInfo.renderPass = renderPass->GetHandle();
		return *this;
	}
	FrameBuffer &FrameBuffer::AttachTexture(Texture *attachment)
	{
		auto extent = attachment->GetImage()->GetExtent();
		mInfo.attachmentCount = 1;
		mInfo.pAttachments = &attachment->GetImage()->GetView();
		mInfo.width = (uint32_t)extent.x;
		mInfo.height = (uint32_t)extent.y;

		return *this;
	}

	const VkFramebuffer &FrameBuffer::GetHandle()
	{
		if (mIsDirty)
		{
			Build();
			mIsDirty = false;
		}
		return mHandle;
	}

	Vec2 FrameBuffer::GetExtent() const
	{
		return {(float)mInfo.width, (float)mInfo.height};
	}

	void FrameBuffer::Build()
	{
		VK_CHECK(vkCreateFramebuffer(mDevice.GetHandle(), &mInfo, nullptr, &mHandle));
	}
}