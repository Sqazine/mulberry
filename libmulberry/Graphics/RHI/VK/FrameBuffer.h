#pragma once
#include <vulkan/vulkan.h>
#include "Texture.h"
#include "RenderPass.h"

namespace mulberry::vk
{
	class FrameBuffer : public Base
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		FrameBuffer& AttachRenderPass(RenderPass* renderPass);
		FrameBuffer& AttachTexture(Texture* attachment);

		const VkFramebuffer &GetHandle();
		Vec2 GetExtent() const;
	private:
		void Build() override;

		VkFramebufferCreateInfo mInfo;
		VkFramebuffer mHandle;
	};
}