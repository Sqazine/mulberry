#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include <optional>
#include "NonCopyable.h"
#include "Utils.h"
#include "Queue.h"
#include "Adapter.h"
#include "CommandPool.h"
#include "CommandBuffer.h"
#include "../Enum.h"

namespace mulberry::vk
{
	class Device : public NonCopyable
	{
	public:
		Device(const PhysicalDeviceSpec &physicalDeviceSpec, const std::vector<const char *> &requiredDeviceExts);
		~Device();

		const VkDevice &GetHandle() const;
		const PhysicalDeviceSpec &GetPhysicalDeviceSpec() const;

		const RasterQueue *GetRasterQueue();
		const ComputeQueue *GetComputeQueue();
		const TransferQueue *GetTransferQueue();
		const PresentQueue *GetPresentQueue();

		class RasterCommandPool *GetRasterCommandPool();
		class ComputeCommandPool *GetComputeCommandPool();
		class TransferCommandPool *GetTransferCommandPool();

		uint32_t FindMemoryType(uint32_t typeFilter, MemoryProperty properties) const;

		void WaitIdle() const;

	private:
		friend class Context;

		const PhysicalDeviceSpec &mPhysicalDeviceSpec;
		VkDevice mHandle;

		std::unique_ptr<RasterQueue> mRasterQueue;
		std::unique_ptr<ComputeQueue> mComputeQueue;
		std::unique_ptr<TransferQueue> mTransferQueue;
		std::unique_ptr<PresentQueue> mPresentQueue;

		std::unique_ptr<RasterCommandPool> mRasterCommandPool;
		std::unique_ptr<ComputeCommandPool> mComputeCommandPool;
		std::unique_ptr<TransferCommandPool> mTransferCommandPool;
	};
}