#pragma once
#include <vector>
#include "Buffer.h"
#include "GraphicsContext.h"

namespace mulberry::vk {

	template <typename T>
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(const std::vector<T>& vertices);
	};

	template <typename T>
	inline VertexBuffer<T>::VertexBuffer(const std::vector<T>& vertices)
		: Buffer(sizeof(T)* vertices.size(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	{

		VkDeviceSize bufferSize = sizeof(T) * vertices.size();
		Buffer stagingBuffer = Buffer(
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		stagingBuffer.Fill(bufferSize, vertices.data());

		Context::GetDevice()->GetGraphicsCommandPool()->SubmitOnce([&stagingBuffer, bufferSize, this](CommandBuffer* cmd)
			{
				VkBufferCopy copyRegion{};
				copyRegion.srcOffset = 0;
				copyRegion.dstOffset = 0;
				copyRegion.size = bufferSize;

				this->CopyFrom(cmd, copyRegion, stagingBuffer);
			});
	}

}