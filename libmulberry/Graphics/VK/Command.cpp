#include "Command.h"
#include "Device.h"
#include "Utils.h"
#include "Context.h"
#include "Queue.h"
#include "Adapter.h"
#include "Logger.h"
#include "Image.h"
#include <iostream>

namespace mulberry::vk
{
	CommandPool::CommandPool(uint32_t queueFamilyIndex)
		: mQueueFamilyIndex(queueFamilyIndex)
	{
		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.pNext = nullptr;
		poolInfo.flags = 0;
		poolInfo.queueFamilyIndex = mQueueFamilyIndex;

		VK_CHECK(vkCreateCommandPool(Context::GetInstance().GetDevice()->GetHandle(), &poolInfo, nullptr, &mCommandPool))
	}
	CommandPool::~CommandPool()
	{
		vkDestroyCommandPool(Context::GetInstance().GetDevice()->GetHandle(), mCommandPool, nullptr);
	}

	const VkCommandPool &CommandPool::GetHandle() const
	{
		return mCommandPool;
	}

	uint32_t CommandPool::GetQueueFamilyIndex() const
	{
		return mQueueFamilyIndex;
	}

	std::unique_ptr<CommandBuffer> CommandPool::CreatePrimaryCommandBuffer()
	{
		return std::move(std::make_unique<CommandBuffer>(*this, VK_COMMAND_BUFFER_LEVEL_PRIMARY));
	}

	void CommandPool::SubmitOnce(std::function<void(class CommandBuffer *)> func) const
	{
		auto commandBuffer = new CommandBuffer(*this, VK_COMMAND_BUFFER_LEVEL_PRIMARY);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.pNext = nullptr;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		beginInfo.pInheritanceInfo = nullptr;

		commandBuffer->Begin(beginInfo);

		func(commandBuffer);

		commandBuffer->End();

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pNext = nullptr;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer->GetHandle();

		const Queue *queue = nullptr;
		if (mQueueFamilyIndex == Context::GetInstance().GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.graphicsFamilyIdx)
			{
				queue = Context::GetInstance().GetDevice()->GetGraphicsQueue();
				((GraphicsQueue*)queue)->Submit(submitInfo);
			}
		else if (mQueueFamilyIndex == Context::GetInstance().GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.computeFamilyIdx)
		{
			queue = Context::GetInstance().GetDevice()->GetComputeQueue();
			((ComputeQueue*)queue)->Submit(submitInfo);
		}
		else if (mQueueFamilyIndex == Context::GetInstance().GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.transferFamilyIdx)
		{
			queue = Context::GetInstance().GetDevice()->GetTransferQueue();
			((TransferQueue*)queue)->Submit(submitInfo);
		}

		queue->WaitIdle();

		delete commandBuffer;
		commandBuffer = nullptr;
	}

	CommandBuffer::CommandBuffer(const CommandPool &commandPool, VkCommandBufferLevel level)
		: mCommandPool(commandPool), mLevel(level)
	{
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.pNext = nullptr;
		allocInfo.level = level;
		allocInfo.commandPool = mCommandPool.GetHandle();
		allocInfo.commandBufferCount = 1;

		VK_CHECK(vkAllocateCommandBuffers(Context::GetInstance().GetDevice()->GetHandle(), &allocInfo, &mCommandBuffer));

		if (mCommandPool.GetQueueFamilyIndex() ==Context::GetInstance().GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.graphicsFamilyIdx)
			mBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		else if (mCommandPool.GetQueueFamilyIndex() == Context::GetInstance().GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.computeFamilyIdx)
			mBindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;
		else
			MULBERRY_CORE_ERROR("Unknown command buffer bind point for queue family index:{}",mCommandPool.GetQueueFamilyIndex());
	}

	CommandBuffer::~CommandBuffer()
	{
		vkFreeCommandBuffers(Context::GetInstance().GetDevice()->GetHandle(), mCommandPool.GetHandle(), 1, &mCommandBuffer);
	}

	const VkCommandBuffer &CommandBuffer::GetHandle() const
	{
		return mCommandBuffer;
	}

	void CommandBuffer::Begin(const VkCommandBufferBeginInfo &beginInfo)
	{
		vkBeginCommandBuffer(mCommandBuffer, &beginInfo);
	}

	void CommandBuffer::End()
	{
		vkEndCommandBuffer(mCommandBuffer);
	}

	void CommandBuffer::BeginRenderPass(const VkRenderPassBeginInfo &renderPassBeginInfo)
	{
		if (mLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
			vkCmdBeginRenderPass(mCommandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
		else if (mLevel == VK_COMMAND_BUFFER_LEVEL_SECONDARY)
			vkCmdBeginRenderPass(mCommandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
	}

	void CommandBuffer::EndRenderPass()
	{
		vkCmdEndRenderPass(mCommandBuffer);
	}

	void CommandBuffer::BindDescriptorSet(const VkPipelineLayout &layout, const VkDescriptorSet &descriptorSet)
	{
		vkCmdBindDescriptorSets(mCommandBuffer, mBindPoint, layout, 0, 1, &descriptorSet, 0, nullptr);
	}

	void CommandBuffer::BindDescriptorSets(const VkPipelineLayout &layout, const std::vector<VkDescriptorSet> &descriptorSets)
	{
		BindDescriptorSets(layout, descriptorSets.size(), descriptorSets.data());
	}

	void CommandBuffer::BindDescriptorSets(const VkPipelineLayout &layout, uint32_t count, const VkDescriptorSet *descriptorSets)
	{
		vkCmdBindDescriptorSets(mCommandBuffer, mBindPoint, layout, 0, count, descriptorSets, 0, nullptr);
	}

	void CommandBuffer::BindPipeline(const VkPipeline &pipeline)
	{
		vkCmdBindPipeline(mCommandBuffer, mBindPoint, pipeline);
	}

	void CommandBuffer::DrawIndexed(uint32_t indexCount)
	{
		vkCmdDrawIndexed(mCommandBuffer, indexCount, 1, 0, 0, 0);
	}

	void CommandBuffer::TransitionImageNewLayout(Image *image, VkImageLayout newLayout)
	{
		VkImageMemoryBarrier barrier{};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.pNext = nullptr;
		barrier.oldLayout = image->GetImageLayout();
		barrier.newLayout = newLayout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = image->GetHandle();
		barrier.subresourceRange.aspectMask = ASPECT_COLOR;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = image->GetMipLevel();
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = 0;

		VkPipelineStageFlags sourceStage;
		VkPipelineStageFlags destinationStage;

		auto oldLayout = barrier.oldLayout;

		if ((oldLayout & VK_IMAGE_LAYOUT_UNDEFINED) == VK_IMAGE_LAYOUT_UNDEFINED && (newLayout & VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
		{
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

			barrier.subresourceRange.aspectMask = ASPECT_DEPTH;

			if (HasStencilComponent(image->GetFormat()))
				barrier.subresourceRange.aspectMask |= ASPECT_STENCIL;

			destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR && newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			barrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_GENERAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			sourceStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

			barrier.subresourceRange.aspectMask = ASPECT_DEPTH;

			if (HasStencilComponent(image->GetFormat()))
				barrier.subresourceRange.aspectMask |= ASPECT_STENCIL;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

			barrier.subresourceRange.aspectMask = ASPECT_DEPTH;

			if (HasStencilComponent(image->GetFormat()))
				barrier.subresourceRange.aspectMask |= ASPECT_STENCIL;

			sourceStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

			barrier.subresourceRange.aspectMask = ASPECT_DEPTH;

			if (HasStencilComponent(image->GetFormat()))
				barrier.subresourceRange.aspectMask |= ASPECT_STENCIL;

			destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			sourceStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else
		{
			throw std::invalid_argument("unsupported layout transition!");
		}

		vkCmdPipelineBarrier(
			mCommandBuffer,
			sourceStage, destinationStage,
			0,
			0, nullptr,
			0, nullptr,
			1, &barrier);
		image->mImageLayout = newLayout;
	}

	void CommandBuffer::CopyBufferToImage(const Buffer *srcBuffer, const Image *dstImage, VkImageLayout imgLayout, const VkBufferImageCopy &region)
	{
		vkCmdCopyBufferToImage(mCommandBuffer, srcBuffer->GetHandle(), dstImage->GetHandle(), imgLayout, 1, &region);
	}
}