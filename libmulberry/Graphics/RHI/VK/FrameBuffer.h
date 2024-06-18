#pragma once
#include <vulkan/vulkan.h>
#include "Texture.h"
#include "RenderPass.h"
#include "Graphics/RHI/Attachment.h"

namespace mulberry::vk
{
	class FrameBuffer : public Base
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		FrameBuffer &AttachRenderPass(RenderPass *renderPass);
		FrameBuffer &BindColorAttachment(uint32_t index, ColorAttachment* attach);

		const VkFramebuffer &GetHandle();
		Vec2 GetExtent();

		ColorAttachment* GetColorAttachment(uint32_t idx) const;

		const std::unordered_map<uint32_t, ColorAttachment*>& GetColorAttachments() const;
	private:
		void Build() override;

		VkFramebufferCreateInfo mInfo;
		VkFramebuffer mHandle;

		std::unordered_map<uint32_t, ColorAttachment*> mAttachments;
	};
}