#pragma once
#include <vulkan/vulkan.h>
#include <cstdint>
#include "Fence.h"

namespace mulberry::vk
{
	class Queue
	{
	public:
		Queue(uint32_t familyIndex);

		void WaitIdle() const;

		const VkQueue &GetHandle() const;

	protected:
		VkQueue mHandle;
	};

	class GraphicsQueue : public Queue
	{
	public:
		GraphicsQueue(uint32_t familyIndex);

		void Submit(const VkSubmitInfo &submitInfo, const Fence *fence = nullptr) const;
	};

	using ComputeQueue = GraphicsQueue;
	using TransferQueue = GraphicsQueue;

	class PresentQueue : public Queue
	{
	public:
		PresentQueue(uint32_t familyIndex);
		void Present(const VkPresentInfoKHR &info) const;
	};
}