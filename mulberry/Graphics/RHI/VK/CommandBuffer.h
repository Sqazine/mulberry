#pragma once
#include <vulkan/vulkan.h>
#include <functional>
#include <vector>
#include <cstdint>
#include "Object.h"
#include "DescriptorSet.h"
#include "PipelineLayout.h"
#include "Pipeline.h"
#include "SyncObject.h"
#include "SwapChain.h"
#include "Buffer.h"

namespace mulberry::vk
{
	class CommandBuffer : public Object
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

		virtual void BindDescriptorSets(PipelineLayout *layout, uint32_t firstSet, const std::vector<const DescriptorSet *> &descriptorSets, const std::vector<uint32_t>& dynamicOffsets = {}) = 0;
		virtual void BindPipeline(class Pipeline *pipeline) const = 0;

		virtual void CopyImage(VkImage srcImage, ImageLayout srcImageLayout, VkImage dstImage, ImageLayout dstImageLayout, const std::vector<VkImageCopy> &copyRegions);
		virtual void CopyImage(VkImage srcImage, ImageLayout rcImageLayout, VkImage dstImage, ImageLayout dstImageLayout, const VkImageCopy &copyRegion);

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

	class RasterCommandBuffer : public CommandBuffer
	{
	public:
		RasterCommandBuffer(VkCommandBufferLevel level);
		~RasterCommandBuffer() override;

		void BindPipeline(Pipeline *pipeline) const override;
		void BindDescriptorSets(PipelineLayout *layout, uint32_t firstSet, const std::vector<const DescriptorSet *> &descriptorSets, const std::vector<uint32_t>& dynamicOffsets = {}) override;

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
		void Present(const std::vector<SwapChain *> swapChains, uint32_t imageIndex, const std::vector<Semaphore *> waitSemaphores = {}) const;
	};

	class ComputeCommandBuffer : public CommandBuffer
	{
	public:
		ComputeCommandBuffer( VkCommandBufferLevel level);
		~ComputeCommandBuffer() override;

		void BindPipeline(Pipeline *pipeline) const override;
		void BindDescriptorSets(PipelineLayout *layout, uint32_t firstSet, const std::vector<const DescriptorSet *> &descriptorSets, const std::vector<uint32_t>& dynamicOffsets = {}) override;

		void Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);

		void Submit(const std::vector<PipelineStage> &waitStages = {}, const std::vector<Semaphore *> waitSemaphores = {}, const std::vector<Semaphore *> signalSemaphores = {}, Fence *fence = nullptr) const override;
	};

	class TransferCommandBuffer : public CommandBuffer
	{
	public:
		TransferCommandBuffer( VkCommandBufferLevel level);
		~TransferCommandBuffer();

		void BindPipeline(Pipeline *pipeline) const override;
		void BindDescriptorSets(PipelineLayout *layout, uint32_t firstSet, const std::vector<const DescriptorSet *> &descriptorSets, const std::vector<uint32_t>& dynamicOffsets = {}) override;

		void Submit(const std::vector<PipelineStage> &waitStages = {}, const std::vector<Semaphore *> waitSemaphores = {}, const std::vector<Semaphore *> signalSemaphores = {}, Fence *fence = nullptr) const override;
	};
}