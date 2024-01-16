#pragma once
#include <vulkan/vulkan.h>
#include <cstdint>
#include "SyncObject.h"

namespace mulberry::vk
{
	class Queue : public Object
	{
	public:
		Queue(uint32_t familyIndex);
		virtual ~Queue();

		void WaitIdle() const;
		const VkQueue &GetHandle() const;
	protected:
		VkQueue mHandle;
	};

	class RasterQueue : public Queue
	{
	public:
		RasterQueue(uint32_t familyIndex);
		~RasterQueue() override;

		void Submit(const VkSubmitInfo &submitInfo, const Fence *fence = nullptr) const;
	};

	using ComputeQueue = RasterQueue;
	using TransferQueue = RasterQueue;

	class PresentQueue : public Queue
	{
	public:
		PresentQueue(uint32_t familyIndex);
		~PresentQueue() override;

		VkResult Present(const VkPresentInfoKHR &info) const;
	};
}