#include "RenderPass.h"
#include "Core/Logger.h"
#include "Utils.h"
#include "Device.h"

namespace mulberry::vk
{
	RenderPass::RenderPass(Format colorformat)
	{
		std::vector<VkAttachmentDescription> attachments;
		std::vector<VkAttachmentReference> colorReferences;

		VkAttachmentDescription colorAttachment{};
		colorAttachment.flags = 0;
		colorAttachment.format = ToVkFormat(colorformat);
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = IMAGE_LAYOUT_CAST(VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL | VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

		attachments.emplace_back(colorAttachment);

		VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		colorReferences.emplace_back(colorAttachmentRef);

		VkSubpassDescription subpass{};
		subpass.flags = 0;
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = colorReferences.size();
		subpass.pColorAttachments = colorReferences.data();
		subpass.pDepthStencilAttachment = nullptr;
		subpass.inputAttachmentCount = 0;
		subpass.pInputAttachments = nullptr;
		subpass.pPreserveAttachments = nullptr;
		subpass.preserveAttachmentCount = 0;
		subpass.pResolveAttachments = nullptr;

		VkSubpassDependency colorDependency{};
		colorDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		colorDependency.dstSubpass = 0;
		colorDependency.srcStageMask = PIPELINE_STAGE_CAST(PipelineStage::COLOR_ATTACHMENT_OUTPUT | PipelineStage::LATE_FRAGMENT_TESTS);
		colorDependency.dstStageMask = PIPELINE_STAGE_CAST(PipelineStage::COLOR_ATTACHMENT_OUTPUT | PipelineStage::LATE_FRAGMENT_TESTS);
		colorDependency.srcAccessMask = 0;
		colorDependency.dstAccessMask = ACCESS_CAST(Access::COLOR_ATTACHMENT_WRITE | Access::DEPTH_STENCIL_ATTACHMENT_WRITE);

		std::vector<VkSubpassDependency> dependencies = {
			colorDependency,
		};

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.pNext = nullptr;
		renderPassInfo.flags = 0;
		renderPassInfo.attachmentCount = attachments.size();
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = dependencies.size();
		renderPassInfo.pDependencies = dependencies.data();

		VK_CHECK(vkCreateRenderPass(mDevice.GetHandle(), &renderPassInfo, nullptr, &mRenderPass))
	}

	RenderPass::~RenderPass()
	{
		vkDestroyRenderPass(mDevice.GetHandle(), mRenderPass, nullptr);
	}

	const VkRenderPass &RenderPass::GetHandle() const
	{
		return mRenderPass;
	}

}