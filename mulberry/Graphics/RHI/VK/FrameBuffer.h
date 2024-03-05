#pragma once
#include <vulkan/vulkan.h>
#include "Texture.h"
#include "RenderPass.h"

namespace mulberry::rhi::vk
{
	class FrameBuffer : public Base
	{
	public:
		FrameBuffer(RenderPass* renderPass,Texture *attachment);
		~FrameBuffer();

		const VkFramebuffer &GetHandle() const;
		const Vec2 &GetExtent() const;
	private:
		Vec2 mExtent;
		VkFramebuffer mHandle;
	};
}