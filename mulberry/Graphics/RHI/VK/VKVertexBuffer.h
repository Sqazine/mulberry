#pragma once
#include <vector>
#include "VKBuffer.h"

namespace mulberry
{
	template <typename T>
	class VKVertexBuffer : public VKGpuBuffer
	{
	public:
		VKVertexBuffer();
		VKVertexBuffer(const std::vector<T> &vertices);
		~VKVertexBuffer();

		void Set(const std::vector<T> &inputArray);

		uint32_t Size();

	private:
		uint32_t mSize;
	};

	template <typename T>
	inline VKVertexBuffer<T>::VKVertexBuffer()
		: VKGpuBuffer(0, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
	{
	}

	template <typename T>
	inline VKVertexBuffer<T>::VKVertexBuffer(const std::vector<T> &vertices)
		: VKGpuBuffer(sizeof(T) * vertices.size(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
	{
		Set(vertices);
	}

	template <typename T>
	inline VKVertexBuffer<T>::~VKVertexBuffer()
	{
	}

	template <typename T>
	inline void VKVertexBuffer<T>::Set(const std::vector<T> &inputArray)
	{
		mSize = inputArray.size();
		VkDeviceSize bufferSize = sizeof(T) * inputArray.size();
		VKCpuBuffer stagingBuffer = VKCpuBuffer(
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT);

		stagingBuffer.Fill(bufferSize, inputArray.data());

		CopyFromStagingBuffer(bufferSize, stagingBuffer);
	}

	template <typename T>
	inline uint32_t VKVertexBuffer<T>::Size()
	{
		return mSize;
	}
}