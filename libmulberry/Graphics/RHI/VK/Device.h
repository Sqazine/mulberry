#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include <optional>
#include "NonCopyable.h"
#include "Utils.h"
#include "Queue.h"
#include "Adapter.h"
#include "Command.h"

#include "../Enum.h"

namespace mulberry::rhi::vk
{
	class Device : public NonCopyable
	{
	public:
		Device(const PhysicalDeviceSpec &physicalDeviceSpec, const std::vector<const char *> &requiredDeviceExts);
		~Device();

		const VkDevice &GetHandle() const;
		const PhysicalDeviceSpec &GetPhysicalDeviceSpec() const;

		const GraphicsQueue *GetGraphicsQueue();
		const ComputeQueue *GetComputeQueue();
		const TransferQueue *GetTransferQueue();
		const PresentQueue *GetPresentQueue();

		class GraphicsCommandPool *GetGraphicsCommandPool();
		class ComputeCommandPool *GetComputeCommandPool();
		class TransferCommandPool *GetTransferCommandPool();

		uint32_t FindMemoryType(uint32_t typeFilter, MemoryProperty properties) const;

		void WaitIdle() const;

	private:

		const PhysicalDeviceSpec &mPhysicalDeviceSpec;
		VkDevice mHandle;

		std::unique_ptr<GraphicsQueue> mGraphicsQueue;
		std::unique_ptr<ComputeQueue> mComputeQueue;
		std::unique_ptr<TransferQueue> mTransferQueue;
		std::unique_ptr<PresentQueue> mPresentQueue;

		std::unique_ptr<GraphicsCommandPool> mGraphicsCommandPool;
		std::unique_ptr<ComputeCommandPool> mComputeCommandPool;
		std::unique_ptr<TransferCommandPool> mTransferCommandPool;
	};
}