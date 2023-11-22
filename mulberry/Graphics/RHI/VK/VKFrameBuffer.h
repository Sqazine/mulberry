#pragma once
#include <vulkan/vulkan.h>
#include "VKRenderPass.h"
#include "VKTexture.h"

namespace mulberry
{
	class VKFrameBuffer
	{
	public:
		VKFrameBuffer(uint32_t width, uint32_t height, const VKRenderPass *renderPass, const std::vector<const VKTexture *> &attachments);
		~VKFrameBuffer();

		const VkFramebuffer &GetHandle() const;

	private:
		VkFramebuffer mFrameBuffer;
	};
}