#pragma once
#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <functional>
#include "VKVertexBuffer.h"
#include "VKIndexBuffer.h"

namespace mulberry
{
	class VKCommandBuffer;

	class VKCommandPool
	{
	public:
		VKCommandPool(uint32_t queueFamilyIndex);
		~VKCommandPool();

		const VkCommandPool &GetHandle() const;
		uint32_t GetQueueFamilyIndex() const;

		std::unique_ptr<class VKCommandBuffer> CreatePrimaryCommandBuffer();
		std::vector<std::unique_ptr<class VKCommandBuffer>> CreatePrimaryCommandBuffers(uint32_t count);

		void SubmitOnce(std::function<void(class VKCommandBuffer *)> func) const;

	private:
		const class VKDevice *mDevice;

		uint32_t mQueueFamilyIndex;
		VkCommandPool mCommandPool;
	};

	class VKCommandBuffer
	{
	public:
		VKCommandBuffer(const VKCommandPool &commandPool, VkCommandBufferLevel level);
		~VKCommandBuffer();

		const VkCommandBuffer &GetHandle() const;

		void Begin();
		void BeginOnce();
		void End();

		void BeginRenderPass(const VkRenderPassBeginInfo &renderPassBeginInfo);
		void EndRenderPass();

		void BindDescriptorSet(const VkPipelineLayout &layout, const VkDescriptorSet &descriptorSet);
		void BindDescriptorSets(const VkPipelineLayout &layout, const std::vector<VkDescriptorSet> &descriptorSets);
		void BindDescriptorSets(const VkPipelineLayout &layout, uint32_t count, const VkDescriptorSet *descriptorSets);

		void BindPipeline(const VkPipeline &pipeline);

		void DrawIndexed(uint32_t indexCount);

		template <typename T>
		void BindVertexBuffer(const VKVertexBuffer<T> &vertexBuffer);

		void BindIndexBuffer(const VKIndexBuffer &indexBuffer);

		void TransitionImageNewLayout(class VKImage *image, VkImageLayout newLayout);

		void CopyBufferToImage(const VKBuffer *srcBuffer, const VKImage *dstImage, VkImageLayout imgLayout, const VkBufferImageCopy &region);

		void Reset();

	private:
		const class VKDevice *mDevice;

		VkPipelineBindPoint mBindPoint;
		VkCommandBufferLevel mLevel;
		const VKCommandPool &mCommandPool;
		VkCommandBuffer mHandle;
	};

	template <typename T>
	inline void VKCommandBuffer::BindVertexBuffer(const VKVertexBuffer<T> &vertexBuffer)
	{
		VkDeviceSize offsets = {0};
		vkCmdBindVertexBuffers(mHandle, 0, 1, &vertexBuffer.GetBuffer(), &offsets);
	}

	inline void VKCommandBuffer::BindIndexBuffer(const VKIndexBuffer &indexBuffer)
	{
		vkCmdBindIndexBuffer(mHandle, indexBuffer.GetHandle(), 0, indexBuffer.GetDataType());
	}
}