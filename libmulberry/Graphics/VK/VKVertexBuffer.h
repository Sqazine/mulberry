#pragma once
#include <vector>
#include "VKBuffer.h"
#include "GraphicsContext.h"

namespace mulberry {

	template <typename T>
	class VKVertexBuffer : public VKBuffer
	{
	public:
		VKVertexBuffer(const std::vector<T>& vertices);
	};

	template <typename T>
	inline VKVertexBuffer<T>::VKVertexBuffer(const std::vector<T>& vertices)
		: Buffer(sizeof(T)* vertices.size(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	{

		VkDeviceSize bufferSize = sizeof(T) * vertices.size();
		VKBuffer stagingBuffer = VKBuffer(
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		stagingBuffer.Fill(bufferSize, vertices.data());

		VKContext::GetDevice()->GetGraphicsCommandPool()->SubmitOnce([&stagingBuffer, bufferSize, this](CommandBuffer* cmd)
			{
				VkBufferCopy copyRegion{};
				copyRegion.srcOffset = 0;
				copyRegion.dstOffset = 0;
				copyRegion.size = bufferSize;

				this->CopyFrom(cmd, copyRegion, stagingBuffer);
			});
	}

}