#pragma once
#include "Buffer.h"

namespace mulberry::vk
{
	template <typename T>
	class UniformBuffer : public Buffer
	{
	public:
		UniformBuffer();

		void Set(const T& data);
	};

	template <typename T>
	inline UniformBuffer<T>::UniformBuffer()
		: Buffer(sizeof(T), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	{
	}
	template <typename T>
	inline void UniformBuffer<T>::Set(const T& data)
	{
		this->Fill(sizeof(T), (void*)&data);
	}
}