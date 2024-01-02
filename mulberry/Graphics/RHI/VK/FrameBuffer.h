#pragma once
#include <vulkan/vulkan.h>
#include "RenderPass.h"
#include "Texture.h"

namespace mulberry::vk
{
	class FrameBuffer : public Object
	{
	public:
		FrameBuffer(uint32_t width, uint32_t height, const RenderPass *renderPass, const Texture *attachments);
		~FrameBuffer();

		const VkFramebuffer &GetHandle() const;

	private:
		VkFramebuffer mHandle;
	};
}