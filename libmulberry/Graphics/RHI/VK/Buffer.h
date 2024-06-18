#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "Defs.h"
#include "Utils.h"
#include "Vec2.h"

namespace mulberry::vk
{
	class Buffer : public Base
	{
	public:
		Buffer(uint64_t size, BufferUsage usage, MemoryProperty property);
		virtual ~Buffer();

		const VkBuffer &GetHandle() const;
		const VkDeviceMemory &GetMemory() const;
		const uint64_t &GetSize() const;

	protected:
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
	};

	class GpuBuffer : public Buffer
	{
	public:
		GpuBuffer(uint64_t size, BufferUsage usage);
		GpuBuffer(const CpuBuffer &srcBuffer, BufferUsage usage);
		~GpuBuffer() override {}

		void UploadDataFrom(uint64_t bufferSize, CpuBuffer &stagingBuffer);
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
	};

	class IndexBuffer : public GpuBuffer
	{
	public:
		IndexBuffer();
		template <typename T>
		IndexBuffer(const std::vector<T> &indices);
		~IndexBuffer() override {}
		template <typename T>
		void Fill(const std::vector<T> &input);
		VkIndexType GetDataType() const;

	private:
		VkIndexType DataStr2VkIndexType(std::string_view dataStr) const;
		VkIndexType mDataType;
	};

	class ShaderStorageBuffer : public GpuBuffer
	{
	public:
		template <typename T>
		ShaderStorageBuffer(const std::vector<T> &vertices);
	};

	template <typename T>
	class UniformBuffer : public CpuBuffer
	{
	public:
		UniformBuffer();
		void Fill(const T &data);
	};

}
#include "Buffer.inl"