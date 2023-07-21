#pragma once
#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <functional>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace mulberry::vk {

	class CommandBuffer;

	class CommandPool
	{
	public:
		CommandPool(uint32_t queueFamilyIndex);
		~CommandPool();

		const VkCommandPool& GetHandle() const;
		uint32_t GetQueueFamilyIndex() const;

		std::unique_ptr<class CommandBuffer> CreatePrimaryCommandBuffer();

		void SubmitOnce(std::function<void(class CommandBuffer*)> func) const;

	private:
		uint32_t mQueueFamilyIndex;
		VkCommandPool mCommandPool;
	};

	class CommandBuffer
	{
	public:
		CommandBuffer(const CommandPool& commandPool, VkCommandBufferLevel level);
		~CommandBuffer();

		const VkCommandBuffer& GetHandle() const;

		void Begin(const VkCommandBufferBeginInfo& beginInfo);
		void End();

		void BeginRenderPass(const VkRenderPassBeginInfo& renderPassBeginInfo);
		void EndRenderPass();

		void BindDescriptorSet(const VkPipelineLayout& layout, const VkDescriptorSet& descriptorSet);
		void BindDescriptorSets(const VkPipelineLayout& layout, const std::vector<VkDescriptorSet>& descriptorSets);
		void BindDescriptorSets(const VkPipelineLayout& layout, uint32_t count, const VkDescriptorSet* descriptorSets);

		void BindPipeline(const VkPipeline& pipeline);

		void DrawIndexed(uint32_t indexCount);
		template <typename T>
		void BindVertexBuffer(const VertexBuffer<T>& vertexBuffer);

		template <typename T>
		void BindIndexBuffer(const IndexBuffer<T>& indexBuffer);

		void TransitionImageNewLayout(class Image* image, VkImageLayout newLayout);

		void CopyBufferToImage(const Buffer* srcBuffer, const Image* dstImage, VkImageLayout imgLayout, const VkBufferImageCopy& region);
	private:
		VkPipelineBindPoint mBindPoint;
		VkCommandBufferLevel mLevel;
		const CommandPool& mCommandPool;
		VkCommandBuffer mCommandBuffer;
	};

	template <typename T>
	inline void CommandBuffer::BindVertexBuffer(const VertexBuffer<T>& vertexBuffer)
	{
		VkDeviceSize offsets = { 0 };
		vkCmdBindVertexBuffers(mCommandBuffer, 0, 1, &vertexBuffer.GetBuffer(), &offsets);
	}

	template <typename T>
	inline void CommandBuffer::BindIndexBuffer(const IndexBuffer<T>& indexBuffer)
	{
		vkCmdBindIndexBuffer(mCommandBuffer, indexBuffer.GetBuffer(), 0, indexBuffer.GetDataType());
	}
}