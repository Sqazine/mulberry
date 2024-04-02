#pragma once
#include <vulkan/vulkan.h>
#include <functional>
#include <vector>
#include <cstdint>
#include "Base.h"
#include "Descriptor.h"
#include "Pipeline.h"
#include "SyncObject.h"
#include "SwapChain.h"
#include "Buffer.h"

namespace mulberry::vk
{

	template <typename T>
	class CommandPool : public Base
	{
	public:
		CommandPool(uint32_t queueFamilyIndex)
		{
			VkCommandPoolCreateInfo info{};
			info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			info.pNext = nullptr;
			info.queueFamilyIndex = queueFamilyIndex;
			info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

			vkCreateCommandPool(mDevice.GetHandle(), &info, nullptr, &mHandle);
		}
		~CommandPool()
		{
			vkDestroyCommandPool(mDevice.GetHandle(), mHandle, nullptr);
		}

		const VkCommandPool &GetHandle() const
		{
			return mHandle;
		}

		std::unique_ptr<T> CreatePrimaryCommandBuffer() const
		{
			return std::move(std::make_unique<T>(VK_COMMAND_BUFFER_LEVEL_PRIMARY));
		}
		std::vector<std::unique_ptr<T>> CreatePrimaryCommandBuffers(uint32_t count) const
		{
			std::vector<std::unique_ptr<T>> result(count);
			for (auto &e : result)
				e = std::move(CreatePrimaryCommandBuffer());
			return std::move(result);
		}

		std::unique_ptr<T> CreateSecondaryCommandBuffer() const
		{
			return std::move(std::make_unique<T>(VK_COMMAND_BUFFER_LEVEL_SECONDARY));
		}
		std::vector<std::unique_ptr<T>> CreateSecondaryCommandBuffers(uint32_t count) const
		{
			std::vector<std::unique_ptr<T>> result(count);
			for (auto &e : result)
				e = std::move(CreateSecondaryCommandBuffer());
			return result;
		}

	private:
		VkCommandPool mHandle;
	};

#define COMMAND_POOL_DECL(name)                                             \
	class name##CommandPool : public CommandPool<class name##CommandBuffer> \
	{                                                                       \
	public:                                                                 \
		name##CommandPool();                                                \
		~name##CommandPool();                                               \
	};

	COMMAND_POOL_DECL(Graphics)
	COMMAND_POOL_DECL(Compute)
	COMMAND_POOL_DECL(Transfer)

	class CommandBuffer : public Base
	{
	public:
		CommandBuffer(VkCommandPool cmdPool, VkCommandBufferLevel level);
		virtual ~CommandBuffer();

		const VkCommandBuffer &GetHandle() const;

		virtual void ExecuteImmediately(const std::function<void()> &func);

		virtual void Begin();
		virtual void End();

		virtual void ImageBarrier(const VkImage &image, Access srcAccess, Access dstAccess, ImageLayout oldLayout, ImageLayout newLayout, const VkImageSubresourceRange &subresourceRange) const;
		virtual void ImageBarrier(const VkImage &image, Format format, ImageLayout oldLayout, ImageLayout newLayout) const;
		virtual void PipelineBarrier(PipelineStage srcStage, PipelineStage dstStage, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier *pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier *pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier *pImageMemoryBarriers) const;

		virtual void BindDescriptorSets(class PipelineLayout *layout, uint32_t firstSet, const std::vector<const DescriptorSet *> &descriptorSets, const std::vector<uint32_t> &dynamicOffsets = {}) = 0;
		virtual void BindPipeline(class Pipeline *pipeline) const = 0;

		virtual void CopyImage(class Image *dstImage, class Image *srcImage, const std::vector<VkImageCopy> &copyRegions);

		virtual void CopyBuffer(const Buffer &dst, const Buffer &src, VkBufferCopy bufferCopy);

		virtual void CopyImageFromBuffer(class Image *dst, Buffer *src);

		virtual void Reset();

		virtual void Submit(const std::vector<PipelineStage> &waitStages = {}, const std::vector<Semaphore *> waitSemaphores = {}, const std::vector<Semaphore *> signalSemaphores = {}, Fence *fence = nullptr) const = 0;

		void TransitionImageNewLayout(class Image *image, ImageLayout newLayout);

	protected:
		virtual void BeginOnce();

		VkCommandPool mRelatedCmdPoolHandle;
		VkCommandBuffer mHandle;
	};

	class GraphicsCommandBuffer : public CommandBuffer
	{
	public:
		GraphicsCommandBuffer(VkCommandBufferLevel level);
		~GraphicsCommandBuffer() override;

		void BindPipeline(Pipeline *pipeline) const override;
		void BindDescriptorSets(class PipelineLayout *layout, uint32_t firstSet, const std::vector<const DescriptorSet *> &descriptorSets, const std::vector<uint32_t> &dynamicOffsets = {}) override;

		void BindVertexBuffers(uint32_t firstBinding, uint32_t bindingCount, const std::vector<VertexBuffer *> &pBuffers, const std::vector<uint64_t> &pOffsets);
		void BindVertexBuffers(uint32_t firstBinding, uint32_t bindingCount, const std::vector<VertexBuffer *> &pBuffers);

		void BeginRenderPass(VkRenderPass renderPass, VkFramebuffer frameBuffer, VkRect2D renderArea, const std::vector<VkClearValue> &clearValues, VkSubpassContents subpassContents);
		void EndRenderPass();

		void SetViewport(const VkViewport &viewport);
		void SetScissor(const VkRect2D &scissor);
		void SetLineWidth(float lineWidth);

		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
		void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);

		void Submit(const std::vector<PipelineStage> &waitStages = {}, const std::vector<Semaphore *> waitSemaphores = {}, const std::vector<Semaphore *> signalSemaphores = {}, Fence *fence = nullptr) const override;
	};

	class ComputeCommandBuffer : public CommandBuffer
	{
	public:
		ComputeCommandBuffer(VkCommandBufferLevel level);
		~ComputeCommandBuffer() override;

		void BindPipeline(Pipeline *pipeline) const override;
		void BindDescriptorSets(class PipelineLayout *layout, uint32_t firstSet, const std::vector<const DescriptorSet *> &descriptorSets, const std::vector<uint32_t> &dynamicOffsets = {}) override;

		void Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);

		void Submit(const std::vector<PipelineStage> &waitStages = {}, const std::vector<Semaphore *> waitSemaphores = {}, const std::vector<Semaphore *> signalSemaphores = {}, Fence *fence = nullptr) const override;
	};

	class TransferCommandBuffer : public CommandBuffer
	{
	public:
		TransferCommandBuffer(VkCommandBufferLevel level);
		~TransferCommandBuffer();

		void BindPipeline(Pipeline *pipeline) const override;
		void BindDescriptorSets(class PipelineLayout *layout, uint32_t firstSet, const std::vector<const DescriptorSet *> &descriptorSets, const std::vector<uint32_t> &dynamicOffsets = {}) override;

		void Submit(const std::vector<PipelineStage> &waitStages = {}, const std::vector<Semaphore *> waitSemaphores = {}, const std::vector<Semaphore *> signalSemaphores = {}, Fence *fence = nullptr) const override;
	};
}