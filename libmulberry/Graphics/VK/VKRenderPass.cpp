#include "VKRenderPass.h"
#include "Logger.h"
#include "VKUtils.h"
#include "VKDevice.h"
#include "VKContext.h"

namespace mulberry {

	VKRenderPass::VKRenderPass(const std::vector<VkFormat>& colorformats)
	{
		std::vector<VkAttachmentDescription> attachments;
		std::vector<VkAttachmentReference> colorReferences;
		for (auto colorFormat : colorformats)
		{
			VkAttachmentDescription colorAttachment{};
			colorAttachment.flags = 0;
			colorAttachment.format = colorFormat;
			colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
			colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
			colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			colorAttachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			attachments.emplace_back(colorAttachment);
		}

		for (int32_t i = 0; i < colorformats.size(); ++i)
		{
			VkAttachmentReference colorAttachmentRef{};
			colorAttachmentRef.attachment = i;
			colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			colorReferences.emplace_back(colorAttachmentRef);
		}

		VkSubpassDescription subpass{};
		subpass.flags = 0;
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = attachments.size() - 1;
		subpass.pColorAttachments = colorReferences.data();
		subpass.pDepthStencilAttachment = nullptr;
		subpass.inputAttachmentCount = 0;
		subpass.pInputAttachments = nullptr;
		subpass.pPreserveAttachments = nullptr;
		subpass.preserveAttachmentCount = 0;
		subpass.pResolveAttachments = nullptr;

		VkSubpassDependency dependency{};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.pNext = nullptr;
		renderPassInfo.flags = 0;
		renderPassInfo.attachmentCount = attachments.size();
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		VK_CHECK(vkCreateRenderPass(VKContext::GetInstance().GetDevice()->GetHandle(), &renderPassInfo, nullptr, &mRenderPass))
	}
	VKRenderPass::~VKRenderPass()
	{
		vkDestroyRenderPass(VKContext::GetInstance().GetDevice()->GetHandle(), mRenderPass, nullptr);
	}

	const VkRenderPass& VKRenderPass::GetHandle() const
	{
		return mRenderPass;
	}

}