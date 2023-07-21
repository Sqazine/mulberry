#pragma once
#include <vulkan/vulkan.h>
#include "RenderPass.h"
#include "ImageView.h"

namespace mulberry::vk 
{

	class FrameBuffer
	{
	public:
		FrameBuffer(uint32_t width, uint32_t height, const RenderPass* renderPass, const std::vector<const ImageView*>& attachments);
		FrameBuffer(uint32_t width, uint32_t height, const RenderPass* renderPass, const std::vector<VkImageView>& attachments);
		~FrameBuffer();

		const VkFramebuffer& GetHandle() const;

	protected:
	private:
		VkFramebuffer mFrameBuffer;
	};
}