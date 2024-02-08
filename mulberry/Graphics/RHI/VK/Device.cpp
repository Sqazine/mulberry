#include "Device.h"
#include <iostream>
#include "Context.h"

#include "Command.h"
#include "Utils.h"
#include "Logger.h"

namespace mulberry::rhi::vk
{
	Device::Device(const PhysicalDeviceSpec &physicalDeviceSpec, const std::vector<const char *> &requiredDeviceExts)
		: mPhysicalDeviceSpec(physicalDeviceSpec)
	{
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		const float queuePriorities = 1.0f;
		VkDeviceQueueCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = 0;
		info.pQueuePriorities = &queuePriorities;
		info.queueCount = 1;
		if (mPhysicalDeviceSpec.queueFamilyIndices.IsSameFamilyIndex())
		{
			info.queueFamilyIndex = mPhysicalDeviceSpec.queueFamilyIndices.graphicsFamilyIdx.value();
			queueCreateInfos.emplace_back(info);
		}
		else
		{
			for (auto idx : mPhysicalDeviceSpec.queueFamilyIndices.IndexArray())
			{
				info.queueFamilyIndex = idx;
				queueCreateInfos.emplace_back(info);
			}
		}

		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pNext = nullptr;
		deviceCreateInfo.flags = 0;
		deviceCreateInfo.pEnabledFeatures = &mPhysicalDeviceSpec.features;
		deviceCreateInfo.queueCreateInfoCount = queueCreateInfos.size();
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.enabledExtensionCount = requiredDeviceExts.size();
		deviceCreateInfo.ppEnabledExtensionNames = requiredDeviceExts.data();

		VK_CHECK(vkCreateDevice(mPhysicalDeviceSpec.handle, &deviceCreateInfo, nullptr, &mHandle));
	}
	Device::~Device()
	{
		WaitIdle();
	
		mRasterQueue.reset(nullptr);
		mPresentQueue.reset(nullptr);
		mComputeQueue.reset(nullptr);
		mTransferQueue.reset(nullptr);
		mComputeCommandPool.reset(nullptr);
		mRasterCommandPool.reset(nullptr);
		mTransferCommandPool.reset(nullptr);
		vkDestroyDevice(mHandle, nullptr);
	}

	void Device::WaitIdle() const
	{
		vkDeviceWaitIdle(mHandle);
	}

	const VkDevice &Device::GetHandle() const
	{
		return mHandle;
	}

	const PhysicalDeviceSpec &Device::GetPhysicalDeviceSpec() const
	{
		return mPhysicalDeviceSpec;
	}

	const RasterQueue *Device::GetRasterQueue()
	{
		if (mRasterQueue == nullptr)
			mRasterQueue = std::make_unique<RasterQueue>(mPhysicalDeviceSpec.queueFamilyIndices.graphicsFamilyIdx.value());
		return mRasterQueue.get();
	}

	const ComputeQueue *Device::GetComputeQueue()
	{
		if (mComputeQueue == nullptr)
			mComputeQueue = std::make_unique<ComputeQueue>(mPhysicalDeviceSpec.queueFamilyIndices.computeFamilyIdx.value());
		return mComputeQueue.get();
	}

	const TransferQueue *Device::GetTransferQueue()
	{
		if (mTransferQueue == nullptr)
			mTransferQueue = std::make_unique<TransferQueue>(mPhysicalDeviceSpec.queueFamilyIndices.transferFamilyIdx.value());
		return mTransferQueue.get();
	}

	const PresentQueue *Device::GetPresentQueue()
	{
		if (mPresentQueue == nullptr)
			mPresentQueue = std::make_unique<PresentQueue>(mPhysicalDeviceSpec.queueFamilyIndices.presentFamilyIdx.value());
		return mPresentQueue.get();
	}

	RasterCommandPool *Device::GetRasterCommandPool()
	{
		if (mRasterCommandPool == nullptr)
			mRasterCommandPool = std::make_unique<RasterCommandPool>();
		return mRasterCommandPool.get();
	}

	ComputeCommandPool *Device::GetComputeCommandPool()
	{
		if (mComputeCommandPool == nullptr)
			mComputeCommandPool = std::make_unique<ComputeCommandPool>();
		return mComputeCommandPool.get();
	}

	TransferCommandPool *Device::GetTransferCommandPool()
	{
		if (mTransferCommandPool == nullptr)
			mTransferCommandPool = std::make_unique<TransferCommandPool>();
		return mTransferCommandPool.get();
	}

	uint32_t Device::FindMemoryType(uint32_t typeFilter, MemoryProperty properties) const
	{
		for (uint32_t i = 0; i < mPhysicalDeviceSpec.memoryProps.memoryTypeCount; ++i)
			if ((typeFilter & (1 << i)) && (mPhysicalDeviceSpec.memoryProps.memoryTypes[i].propertyFlags & MEMORY_PROPERTY_CAST(properties)) == MEMORY_PROPERTY_CAST(properties))
				return i;

		MULBERRY_CORE_ERROR("Failed to find suitable memory type!");
		return -1;
	}
}