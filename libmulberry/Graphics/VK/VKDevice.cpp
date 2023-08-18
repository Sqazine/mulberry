#include "VKDevice.h"
#include <iostream>
#include "VKContext.h"
#include "VKCommand.h"
#include "VKUtils.h"
#include "Logger.h"

namespace mulberry {

	VKDevice::VKDevice(const PhysicalDeviceSpec& physicalDeviceSpec)
		:mPhysicalDeviceSpec(physicalDeviceSpec)
	{
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		if (mPhysicalDeviceSpec.queueFamilyIndices.IsSameFamilyIndex())
		{
			const float queuePriorities[3]{ 1, 1, 1 };
			VkDeviceQueueCreateInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			info.pNext = nullptr;
			info.flags = 0;
			info.pQueuePriorities = queuePriorities;
			info.queueCount = 3;
			info.queueFamilyIndex = mPhysicalDeviceSpec.queueFamilyIndices.graphicsFamilyIdx.value();
			queueCreateInfos.emplace_back(info);
		}
		else
		{
			const float queuePriorities = 1.0f;

			for (auto idx : mPhysicalDeviceSpec.queueFamilyIndices.IndexArray())
			{
				VkDeviceQueueCreateInfo info = {};
				info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				info.pNext = nullptr;
				info.flags = 0;
				info.pQueuePriorities = &queuePriorities;
				info.queueCount = 1;
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

		VK_CHECK(vkCreateDevice(mPhysicalDeviceSpec.handle, &deviceCreateInfo, nullptr, &mHandle));
	}
	VKDevice::~VKDevice()
	{
		mGraphicsQueue.reset(nullptr);
		mComputeQueue.reset(nullptr);
		mTransferQueue.reset(nullptr);
		mComputeCommandPool.reset(nullptr);
		mGraphicsCommandPool.reset(nullptr);
		mTransferCommandPool.reset(nullptr);
		WaitIdle();
		vkDestroyDevice(mHandle, nullptr);
	}

	void VKDevice::WaitIdle() const
	{
		vkDeviceWaitIdle(mHandle);
	}

	const VkDevice& VKDevice::GetHandle() const
	{
		return mHandle;
	}

	const PhysicalDeviceSpec &VKDevice::GetPhysicalDeviceSpec() const
	{
		return mPhysicalDeviceSpec;
	}

	const VKGraphicsQueue* VKDevice::GetGraphicsQueue()
	{
		if (mGraphicsQueue == nullptr)
			mGraphicsQueue = std::make_unique<VKGraphicsQueue>(mPhysicalDeviceSpec.queueFamilyIndices.graphicsFamilyIdx.value());
		return mGraphicsQueue.get();
	}

	const VKComputeQueue* VKDevice::GetComputeQueue()
	{
		if (mComputeQueue == nullptr)
			mComputeQueue = std::make_unique<VKComputeQueue>(mPhysicalDeviceSpec.queueFamilyIndices.computeFamilyIdx.value());
		return mComputeQueue.get();
	}

	const VKTransferQueue* VKDevice::GetTransferQueue()
	{
		if (mTransferQueue == nullptr)
			mTransferQueue = std::make_unique<VKTransferQueue>(mPhysicalDeviceSpec.queueFamilyIndices.transferFamilyIdx.value());
		return mTransferQueue.get();
	}

	VKCommandPool* VKDevice::GetGraphicsCommandPool()
	{
		if (mGraphicsCommandPool == nullptr)
			mGraphicsCommandPool = std::make_unique<VKCommandPool>(mPhysicalDeviceSpec.queueFamilyIndices.graphicsFamilyIdx.value());
		return mGraphicsCommandPool.get();
	}

	VKCommandPool* VKDevice::GetComputeCommandPool()
	{
		if (mComputeCommandPool == nullptr)
			mComputeCommandPool = std::make_unique<VKCommandPool>(mPhysicalDeviceSpec.queueFamilyIndices.computeFamilyIdx.value());
		return mComputeCommandPool.get();
	}

	VKCommandPool* VKDevice::GetTransferCommandPool()
	{
		if (mTransferCommandPool == nullptr)
			mTransferCommandPool = std::make_unique<VKCommandPool>(mPhysicalDeviceSpec.queueFamilyIndices.transferFamilyIdx.value());
		return mTransferCommandPool.get();
	}

	uint32_t VKDevice::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const
	{
		for (uint32_t i = 0; i < mPhysicalDeviceSpec.memoryProps.memoryTypeCount; ++i)
			if ((typeFilter & (1 << i)) && (mPhysicalDeviceSpec.memoryProps.memoryTypes[i].propertyFlags & properties) == properties)
				return i;

		MULBERRY_CORE_ERROR("Failed to find suitable memory type!");
		return -1;
	}
}