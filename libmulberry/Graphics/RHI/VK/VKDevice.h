#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include <optional>
#include "NonCopyable.h"
#include "VKUtils.h"
#include "VKQueue.h"
#include "VKAdapter.h"

namespace mulberry
{
	class VKDevice : public NonCopyable
	{
	public:
		VKDevice(const PhysicalDeviceSpec &physicalDeviceSpec,const std::vector<const char*>& requiredDeviceExts);
		~VKDevice();

		const VkDevice &GetHandle() const;
		const PhysicalDeviceSpec &GetPhysicalDeviceSpec() const;

		const VKGraphicsQueue *GetGraphicsQueue();
		const VKComputeQueue *GetComputeQueue();
		const VKTransferQueue *GetTransferQueue();

		class VKCommandPool *GetGraphicsCommandPool();
		class VKCommandPool *GetComputeCommandPool();
		class VKCommandPool *GetTransferCommandPool();

		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;

		void WaitIdle() const;

	private:
		const PhysicalDeviceSpec &mPhysicalDeviceSpec;
		VkDevice mHandle;

		std::unique_ptr<VKGraphicsQueue> mGraphicsQueue;
		std::unique_ptr<VKComputeQueue> mComputeQueue;
		std::unique_ptr<VKTransferQueue> mTransferQueue;

		std::unique_ptr<class VKCommandPool> mGraphicsCommandPool;
		std::unique_ptr<class VKCommandPool> mComputeCommandPool;
		std::unique_ptr<class VKCommandPool> mTransferCommandPool;
	};
}