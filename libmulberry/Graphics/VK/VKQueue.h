#pragma once
#include <vulkan/vulkan.h>
#include <cstdint>
#include "VKFence.h"

namespace mulberry
{
	class VKQueue
	{
	public:
		VKQueue(uint32_t familyIndex);

		void WaitIdle() const;

		const VkQueue &GetHandle() const;

	protected:
		VkQueue mHandle;
	};

	class VKGraphicsQueue : public VKQueue
	{
	public:
		VKGraphicsQueue(uint32_t familyIndex);

		void Submit(const VkSubmitInfo &submitInfo, const VKFence *fence = nullptr) const;
	};

	using VKComputeQueue = VKGraphicsQueue;
	using VKTransferQueue = VKGraphicsQueue;

	class VKPresentQueue : public VKQueue
	{
	public:
		VKPresentQueue(uint32_t familyIndex);
		void Present(const VkPresentInfoKHR &info) const;
	};
}