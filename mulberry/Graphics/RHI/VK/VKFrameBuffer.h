#pragma once
#include <vulkan/vulkan.h>
#include "VKRenderPass.h"
#include "VKImageView.h"

namespace mulberry
{
	class VKFrameBuffer
	{
	public:
		VKFrameBuffer(uint32_t width, uint32_t height, const VKRenderPass *renderPass, const std::vector<const VKImageView *> &attachments);
		VKFrameBuffer(uint32_t width, uint32_t height, const VKRenderPass *renderPass, const std::vector<VkImageView> &attachments);
		~VKFrameBuffer();

		const VkFramebuffer &GetHandle() const;

	private:
		const class VKDevice* mDevice;

		VkFramebuffer mFrameBuffer;
	};
}