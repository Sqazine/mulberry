#pragma once
#include <vulkan/vulkan.h>
#include <cstdint>
#include "SyncObject.h"

namespace mulberry::vk
{
	class Queue : public Base
	{
	public:
		Queue(uint32_t familyIndex);
		virtual ~Queue();

		void WaitIdle() const;
		const VkQueue &GetHandle() const;
	protected:
		VkQueue mHandle;
	};

	class GraphicsQueue : public Queue
	{
	public:
		GraphicsQueue(uint32_t familyIndex);
		~GraphicsQueue() override;
	private:
		friend class CommandBuffer;
		void Submit(const VkSubmitInfo &submitInfo, const Fence *fence = nullptr) const;
	};

	using ComputeQueue = GraphicsQueue;
	using TransferQueue = GraphicsQueue;

	class PresentQueue : public Queue
	{
	public:
		PresentQueue(uint32_t familyIndex);
		~PresentQueue() override;
	private:
		friend class SwapChain;
		VkResult Present(const VkPresentInfoKHR &info) const;
	};
}