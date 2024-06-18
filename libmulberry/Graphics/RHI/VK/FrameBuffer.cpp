#include "FrameBuffer.h"
#include "GraphicsContext.h"
#include "Utils.h"
#include "Logger.h"
#include "App.h"
#include "Image.h"
#include "Graphics/RHI/Attachment.h"

namespace mulberry::vk
{
	FrameBuffer::FrameBuffer()
		: mHandle(VK_NULL_HANDLE), mInfo({})
	{
		mInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		mInfo.pNext = nullptr;
		mInfo.flags = 0;
		mInfo.layers = 1;

		mIsDirty = true;
	}

	FrameBuffer::~FrameBuffer()
	{
		if (mHandle)
			vkDestroyFramebuffer(VK_DEVICE->GetHandle(), mHandle, nullptr);
	}

	FrameBuffer &FrameBuffer::AttachRenderPass(RenderPass *renderPass)
	{
		SET(mInfo.renderPass, renderPass->GetHandle());
	}

	FrameBuffer &FrameBuffer::BindColorAttachment(uint32_t index, ColorAttachment *attach)
	{
		mAttachments[index] = attach;
		mIsDirty = true;
		return *this;
	}

	const VkFramebuffer &FrameBuffer::GetHandle()
	{
		if (mIsDirty || mHandle == VK_NULL_HANDLE)
			Build();
		return mHandle;
	}

	Vec2 FrameBuffer::GetExtent()
	{
		if (mIsDirty || mHandle == VK_NULL_HANDLE)
			Build();
		return {(float)mInfo.width, (float)mInfo.height};
	}

		ColorAttachment* FrameBuffer::GetColorAttachment(uint32_t idx) const
		{
			auto iter=mAttachments.find(idx);
			return iter->second;
		}

	const std::unordered_map<uint32_t, ColorAttachment*>& FrameBuffer::GetColorAttachments() const
	{
		return mAttachments;
	}

	void FrameBuffer::Build()
	{
		uint32_t maxWidth=0;
		uint32_t maxHeight=0;
		std::vector<VkImageView> rawViews;
		for (auto [k, v] : mAttachments)
		{
			auto extent = v->texture->GetVkImpl()->GetImage()->GetExtent();
			if (maxWidth < extent.x)
				maxWidth = extent.x;
			if (maxHeight < extent.y)
				maxHeight = extent.y;
			rawViews.emplace_back(v->texture->GetVkImpl()->GetImage()->GetView());
		}

		mInfo.attachmentCount = rawViews.size();
		mInfo.pAttachments = rawViews.data();
		mInfo.width = maxWidth;
		mInfo.height = maxHeight;

		VK_CHECK(vkCreateFramebuffer(mDevice.GetHandle(), &mInfo, nullptr, &mHandle));

		mIsDirty = false;
	}
}