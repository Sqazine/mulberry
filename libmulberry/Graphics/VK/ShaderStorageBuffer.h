#pragma once
#include "Buffer.h"
namespace mulberry::vk {
	template <typename T>
	class ShaderStorageBuffer : public Buffer
	{
	public:
		ShaderStorageBuffer(const std::vector<T>& vertices);
	};

	template <typename T>
	inline ShaderStorageBuffer<T>::ShaderStorageBuffer(const std::vector<T>& bufferData)
		: Buffer(sizeof(T)* bufferData.size(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	{

		VkDeviceSize bufferSize = sizeof(T) * bufferData.size();
		Buffer stagingBuffer = Buffer(
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		stagingBuffer.Fill(bufferSize, bufferData.data());

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