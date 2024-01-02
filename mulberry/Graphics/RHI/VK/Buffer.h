#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "Object.h"
#include "Utils.h"
#include "Vec2.h"
#include "Enum.h"

namespace mulberry::vk
{
	class Buffer : public Object
	{
	public:
		Buffer(uint64_t size, BufferUsage usage, MemoryProperty property);
		virtual ~Buffer();

		const VkBuffer &GetHandle() const;
		const VkDeviceMemory &GetMemory() const;
		const uint64_t &GetSize() const;

	protected:
		VkMemoryRequirements GetMemoryRequirements() const;

		VkBuffer mBuffer;
		VkDeviceMemory mBufferMemory;
		uint64_t mSize;
	};

	class CpuBuffer : public Buffer
	{
	public:
		CpuBuffer(uint64_t size, BufferUsage usage);
		~CpuBuffer() override {}

		template <typename T>
		CpuBuffer(const std::vector<T> &srcData, BufferUsage usage);

		void Fill(size_t size, const void *data);
		void CopyFrom(class CommandBuffer *commandBuffer, VkBufferCopy bufferCopy, const CpuBuffer &buffer);
	};

	template <typename T>
	CpuBuffer::CpuBuffer(const std::vector<T> &srcData, BufferUsage usage)
		: Buffer(srcData.data(), sizeof(T) * srcData.size(), usage, MemoryProperty::HOST_VISIBLE | MemoryProperty::HOST_COHERENT)
	{
	}

	class GpuBuffer : public Buffer
	{
	public:
		GpuBuffer(uint64_t size, BufferUsage usage);
		GpuBuffer(const CpuBuffer &srcBuffer, BufferUsage usage);
		~GpuBuffer() override {}

		void UploadDataFrom(uint64_t bufferSize, CpuBuffer &stagingBuffer);

	private:
	};

	class VertexBuffer : public GpuBuffer
	{
	public:
		VertexBuffer() : GpuBuffer(0, BufferUsage::TRANSFER_DST | BufferUsage::VERTEX) {}

		template <typename T>
		VertexBuffer(const std::vector<T> &vertices);

		~VertexBuffer() override {}

		template <typename T>
		void Fill(const std::vector<T> &inputArray);
		uint32_t Size();

	private:
		uint32_t mSize;
	};

	template <typename T>
	inline VertexBuffer::VertexBuffer(const std::vector<T> &vertices)
		: GpuBuffer(sizeof(T) * vertices.size(), BufferUsage::TRANSFER_DST | BufferUsage::VERTEX)
	{
		Fill(vertices);
	}

	template <typename T>
	inline void VertexBuffer::Fill(const std::vector<T> &inputArray)
	{
		mSize = inputArray.size();
		uint64_t bufferSize = sizeof(T) * inputArray.size();
		CpuBuffer stagingBuffer = CpuBuffer(bufferSize, BufferUsage::TRANSFER_SRC);

		stagingBuffer.Fill(bufferSize, inputArray.data());

		UploadDataFrom(bufferSize, stagingBuffer);
	}

	inline uint32_t VertexBuffer::Size()
	{
		return mSize;
	}

	class IndexBuffer : public GpuBuffer
	{
	public:
		IndexBuffer();
		template <typename T>
		IndexBuffer(const std::vector<T> &indices);
		~IndexBuffer() override {}
		template <typename T>
		void Fill(const std::vector<T> &input);
		uint32_t Size() const;
		VkIndexType GetDataType() const;

	private:
		VkIndexType DataStr2VkIndexType(std::string_view dataStr) const;
		uint32_t mSize;
		VkIndexType mDataType;
	};

	inline IndexBuffer::IndexBuffer()
		: GpuBuffer(0, BufferUsage::TRANSFER_DST | BufferUsage::INDEX)
	{
	}

	template <typename T>
	inline IndexBuffer::IndexBuffer(const std::vector<T> &indices)
		: GpuBuffer(sizeof(T) * indices.size(), BufferUsage::TRANSFER_DST | BufferUsage::INDEX)
	{
		Fill(indices);
	}

	template <typename T>
	inline void IndexBuffer::Fill(const std::vector<T> &input)
	{
		mSize = input.size();
		mDataType = DataStr2VkIndexType(typeid(T).name());
		uint64_t bufferSize = sizeof(T) * input.size();
		CpuBuffer stagingBuffer = CpuBuffer(bufferSize, BufferUsage::TRANSFER_SRC);
		stagingBuffer.Fill(bufferSize, input.data());
		UploadDataFrom(bufferSize, stagingBuffer);
	}

	inline uint32_t IndexBuffer::Size() const
	{
		return mSize;
	}

	inline VkIndexType IndexBuffer::GetDataType() const
	{
		return mDataType;
	}

	inline VkIndexType IndexBuffer::DataStr2VkIndexType(std::string_view dataStr) const
	{
		if (dataStr.compare("uint32_t") == 0 || dataStr.compare("unsigned int") == 0)
			return VK_INDEX_TYPE_UINT32;
		else if (dataStr.compare("uint8_t") == 0 || dataStr.compare("unsigned char") == 0)
			return VK_INDEX_TYPE_UINT8_EXT;
		else if (dataStr.compare("uint16_t") == 0 || dataStr.compare("unsigned short") == 0)
			return VK_INDEX_TYPE_UINT16;
		return VK_INDEX_TYPE_UINT32;
	}

	class ShaderStorageBuffer : public GpuBuffer
	{
	public:
		template <typename T>
		ShaderStorageBuffer(const std::vector<T> &vertices);
	};

	template <typename T>
	inline ShaderStorageBuffer::ShaderStorageBuffer(const std::vector<T> &bufferData)
		: Buffer(sizeof(T) * bufferData.size(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	{
		uint64_t bufferSize = sizeof(T) * bufferData.size();
		CpuBuffer stagingBuffer = CpuBuffer(bufferSize, BufferUsage::TRANSFER_SRC);
		stagingBuffer.Fill(bufferSize, bufferData.data());

		CopyFromStagingBuffer(bufferSize, stagingBuffer);
	}

	template <typename T>
	class UniformBuffer : public Buffer
	{
	public:
		UniformBuffer();

		void Set(const T &data);
	};

	template <typename T>
	inline UniformBuffer<T>::UniformBuffer()
		: Buffer(sizeof(T), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	{
	}
	template <typename T>
	inline void UniformBuffer<T>::Set(const T &data)
	{
		this->Fill(sizeof(T), (void *)&data);
	}
}