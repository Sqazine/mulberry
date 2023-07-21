#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include <optional>
#include "Utils.h"
#include "Queue.h"
#include "NonCopyable.h"
#include "Adapter.h"

namespace mulberry::vk
{

	class Device : public NonCopyable
	{
	public:
		Device(const PhysicalDeviceSpec &physicalDeviceSpec);
		~Device();

		const VkDevice &GetHandle() const;
		const PhysicalDeviceSpec &GetPhysicalDeviceSpec() const;

		const GraphicsQueue *GetGraphicsQueue();
		const ComputeQueue *GetComputeQueue();
		const TransferQueue *GetTransferQueue();

		class CommandPool *GetGraphicsCommandPool();
		class CommandPool *GetComputeCommandPool();
		class CommandPool *GetTransferCommandPool();

		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;

		void WaitIdle() const;

	private:
		const PhysicalDeviceSpec &mPhysicalDeviceSpec;
		VkDevice mHandle;

		std::unique_ptr<GraphicsQueue> mGraphicsQueue;
		std::unique_ptr<ComputeQueue> mComputeQueue;
		std::unique_ptr<TransferQueue> mTransferQueue;

		std::unique_ptr<class CommandPool> mGraphicsCommandPool;
		std::unique_ptr<class CommandPool> mComputeCommandPool;
		std::unique_ptr<class CommandPool> mTransferCommandPool;
	};
}