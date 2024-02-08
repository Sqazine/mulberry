#pragma once
#include <vulkan/vulkan.h>
#include "RenderPass.h"
#include "Texture.h"

namespace mulberry::rhi::vk
{
	class FrameBuffer : public Object
	{
	public:
		FrameBuffer(uint32_t width, uint32_t height, const RenderPass *renderPass, Texture *attachments);
		~FrameBuffer();

		const VkFramebuffer &GetHandle() const;

		const Vec2& GetExtent() const;
	private:
		Vec2 mExtent;
		VkFramebuffer mHandle;
	};
}