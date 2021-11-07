#include "Device.h"
#include "Context.h"
#include "Instance.h"
#include "Surface.h"
#include "Utils.h"
#include <cassert>
#include <set>

namespace VK
{
	PhysicalDevice::PhysicalDevice()
		: m_PhysicalDeviceHandle(VK_NULL_HANDLE)
	{
	}

	PhysicalDevice::~PhysicalDevice()
	{
	}

	bool PhysicalDevice::IsExtensionSupport(std::string_view extName)
	{
		for (const auto& extProp : m_PhysicalDeviceExtensionProps)
			if (extProp.extensionName == extName)
				return true;
		return false;
	}

	bool PhysicalDevice::IsLayerSupport(std::string_view layerName)
	{
		for (const auto& layer : m_PhysicalDeviceLayerProps)
			if (layer.layerName == layerName)
				return true;
		return false;
	}

	PhysicalDeviceList::PhysicalDeviceList()
		: m_BestPhysicalDeviceIdx(0)
	{
		EnumeratePhysicalDevices();
		EnumeratePhysicalDeviceProps();
		EnumeratePhysicalDeviceFeatures();
		EnumeratePhysicalDeviceExtensions();
		EnumeratePhysicalDeviceLayerProps();
		EnumeratePhysicalDeviceMemoryProps();
		EnumeratePhysicalDeviceQueueFamilyProps();
		EnumeratePhysicalDeviceSwapChainDetails();
		EnumeratePhysicalDeviceQueueFamilies();
	}
	PhysicalDeviceList::~PhysicalDeviceList()
	{
	}

	PhysicalDevice PhysicalDeviceList::GetSuitablePhysicalDevice()
	{
		//TODO
		return m_PhysicalDeviceList[m_BestPhysicalDeviceIdx];
	}

	void PhysicalDeviceList::EnumeratePhysicalDevices()
	{
		uint32_t physicalDeviceCount = 0;
		vkEnumeratePhysicalDevices(Context::m_Instance.get()->m_InstanceHandle, &physicalDeviceCount, nullptr);

		assert(physicalDeviceCount != 0);

		std::vector<VkPhysicalDevice> phyDevices;

		phyDevices.resize(physicalDeviceCount);
		vkEnumeratePhysicalDevices(Context::m_Instance.get()->m_InstanceHandle, &physicalDeviceCount, phyDevices.data());

		for (const auto& phyDevice : phyDevices)
		{
			PhysicalDevice tmpDevice;
			tmpDevice.m_PhysicalDeviceHandle = phyDevice;
			m_PhysicalDeviceList.emplace_back(tmpDevice);
		}
	}

	void PhysicalDeviceList::EnumeratePhysicalDeviceProps()
	{
		for (auto& phyDevice : m_PhysicalDeviceList)
			vkGetPhysicalDeviceProperties(phyDevice.m_PhysicalDeviceHandle, &phyDevice.m_PhysicalDeviceProps);
	}

	void PhysicalDeviceList::EnumeratePhysicalDeviceFeatures()
	{
		for (auto& phyDevice : m_PhysicalDeviceList)
			vkGetPhysicalDeviceFeatures(phyDevice.m_PhysicalDeviceHandle, &phyDevice.m_PhysicalDeviceFeatures);
	}

	void PhysicalDeviceList::EnumeratePhysicalDeviceExtensions()
	{
		for (auto& phyDevice : m_PhysicalDeviceList)
		{
			uint32_t count;
			vkEnumerateDeviceExtensionProperties(phyDevice.m_PhysicalDeviceHandle, nullptr, &count, nullptr);
			phyDevice.m_PhysicalDeviceExtensionProps.resize(count);
			vkEnumerateDeviceExtensionProperties(phyDevice.m_PhysicalDeviceHandle, nullptr, &count, phyDevice.m_PhysicalDeviceExtensionProps.data());
		}
	}

	void PhysicalDeviceList::EnumeratePhysicalDeviceLayerProps()
	{
		for (auto& phyDevice : m_PhysicalDeviceList)
		{
			uint32_t count;
			vkEnumerateDeviceLayerProperties(phyDevice.m_PhysicalDeviceHandle, &count, nullptr);
			phyDevice.m_PhysicalDeviceLayerProps.resize(count);
			vkEnumerateDeviceLayerProperties(phyDevice.m_PhysicalDeviceHandle, &count, phyDevice.m_PhysicalDeviceLayerProps.data());
		}
	}

	void PhysicalDeviceList::EnumeratePhysicalDeviceMemoryProps()
	{
		for (auto& phyDevice : m_PhysicalDeviceList)
			vkGetPhysicalDeviceMemoryProperties(phyDevice.m_PhysicalDeviceHandle, &phyDevice.m_PhysicalDeviceMemoryProps);
	}

	void PhysicalDeviceList::EnumeratePhysicalDeviceQueueFamilyProps()
	{
		for (auto& phyDevice : m_PhysicalDeviceList)
		{
			uint32_t count;
			vkGetPhysicalDeviceQueueFamilyProperties(phyDevice.m_PhysicalDeviceHandle, &count, nullptr);
			phyDevice.m_PhysicalDeviceQueueFamilyProps.resize(count);
			vkGetPhysicalDeviceQueueFamilyProperties(phyDevice.m_PhysicalDeviceHandle, &count, phyDevice.m_PhysicalDeviceQueueFamilyProps.data());
		}
	}

	void PhysicalDeviceList::EnumeratePhysicalDeviceQueueFamilies()
	{

		for (auto& phyDevice : m_PhysicalDeviceList)
		{

			QueueFamilyIndices result;

			for (size_t i = 0; i < phyDevice.m_PhysicalDeviceQueueFamilyProps.size(); ++i)
			{
				if (phyDevice.m_PhysicalDeviceQueueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
					result.graphicsFamily = i;
				if (phyDevice.m_PhysicalDeviceQueueFamilyProps[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
					result.computeFamily = i;
				if (phyDevice.m_PhysicalDeviceQueueFamilyProps[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
					result.transferFamily = i;
				if (phyDevice.m_PhysicalDeviceQueueFamilyProps[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
					result.sparseBindingFamily = i;

				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(phyDevice.m_PhysicalDeviceHandle, i, Context::m_Surface.get()->m_SurfaceHandle, &presentSupport);
				if (presentSupport)
					result.presentFamily = i;
			}

			phyDevice.m_QueueFamilyIndices = result;
		}
	}

	void PhysicalDeviceList::EnumeratePhysicalDeviceSwapChainDetails()
	{
		SwapChainDetails tmp;
		for (auto& phyDevice : m_PhysicalDeviceList)
		{
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(phyDevice.m_PhysicalDeviceHandle, Context::m_Surface->m_SurfaceHandle, &tmp.surfaceCapabilities);

			uint32_t formatCount;
			vkGetPhysicalDeviceSurfaceFormatsKHR(phyDevice.m_PhysicalDeviceHandle, Context::m_Surface->m_SurfaceHandle, &formatCount, nullptr);
			if (formatCount > 0)
			{
				tmp.surfaceFormats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(phyDevice.m_PhysicalDeviceHandle, Context::m_Surface->m_SurfaceHandle, &formatCount, tmp.surfaceFormats.data());
			}
			uint32_t presentModeCount;
			vkGetPhysicalDeviceSurfacePresentModesKHR(phyDevice.m_PhysicalDeviceHandle, Context::m_Surface->m_SurfaceHandle, &presentModeCount, nullptr);
			if (presentModeCount > 0)
			{
				tmp.presentModes.resize(presentModeCount);
				vkGetPhysicalDeviceSurfacePresentModesKHR(phyDevice.m_PhysicalDeviceHandle, Context::m_Surface->m_SurfaceHandle, &presentModeCount, tmp.presentModes.data());
			}
			phyDevice.m_SwapChainDetails = tmp;
		}
	}

	LogicalDevice::LogicalDevice()
		: m_LogicalDeviceHandle(VK_NULL_HANDLE)
	{
		PhysicalDevice bestPhyDevice = Context::m_PhysicalDeviceList->GetSuitablePhysicalDevice();

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		QueueFamilyIndices tmpIndices = bestPhyDevice.m_QueueFamilyIndices;
		std::set<uint32_t> queueFamilies;
		if (tmpIndices.graphicsFamily.has_value())
			queueFamilies.emplace(tmpIndices.graphicsFamily.value());
		if (tmpIndices.presentFamily.has_value())
			queueFamilies.emplace(tmpIndices.presentFamily.value());
		if (tmpIndices.computeFamily.has_value())
			queueFamilies.emplace(tmpIndices.computeFamily.value());
		if (tmpIndices.transferFamily.has_value())
			queueFamilies.emplace(tmpIndices.transferFamily.value());
		if (tmpIndices.sparseBindingFamily.has_value())
			queueFamilies.emplace(tmpIndices.sparseBindingFamily.value());

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : queueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{
				.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0,
				.queueFamilyIndex = queueFamily,
				.queueCount = 1,
				.pQueuePriorities = &queuePriority,
			};
			queueCreateInfos.emplace_back(queueCreateInfo);
		}

		std::vector<const char*> extNames;
		for (const auto& extProp : bestPhyDevice.m_PhysicalDeviceExtensionProps)
			extNames.emplace_back(extProp.extensionName);

		std::vector<const char*> layNames;
		for (const auto& layProp : bestPhyDevice.m_PhysicalDeviceLayerProps)
			layNames.emplace_back(layProp.layerName);

		VkDeviceCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.queueCreateInfoCount = (uint32_t)queueCreateInfos.size(),
			.pQueueCreateInfos = queueCreateInfos.data(),
			.enabledLayerCount = Context::m_RenderCreateInfo.useValidationLayer ? (uint32_t)layNames.size() : 0,
			.ppEnabledLayerNames = Context::m_RenderCreateInfo.useValidationLayer ? layNames.data() : nullptr,
			.enabledExtensionCount = (uint32_t)extNames.size(),
			.ppEnabledExtensionNames = extNames.data(),
			.pEnabledFeatures = &bestPhyDevice.m_PhysicalDeviceFeatures,
		};

		VK_CHECK_RESULT(vkCreateDevice(bestPhyDevice.m_PhysicalDeviceHandle, &createInfo, nullptr, &m_LogicalDeviceHandle));

		if (tmpIndices.graphicsFamily.has_value())
			vkGetDeviceQueue(m_LogicalDeviceHandle, tmpIndices.graphicsFamily.value(), 0, &m_Queues.graphicsQueue);
		if (tmpIndices.presentFamily.has_value())
			vkGetDeviceQueue(m_LogicalDeviceHandle, tmpIndices.presentFamily.value(), 0, &m_Queues.presentQueue);
		if (tmpIndices.computeFamily.has_value())
			vkGetDeviceQueue(m_LogicalDeviceHandle, tmpIndices.computeFamily.value(), 0, &m_Queues.computeQueue);
		if (tmpIndices.transferFamily.has_value())
			vkGetDeviceQueue(m_LogicalDeviceHandle, tmpIndices.transferFamily.value(), 0, &m_Queues.transferQueue);
		if (tmpIndices.sparseBindingFamily.has_value())
			vkGetDeviceQueue(m_LogicalDeviceHandle, tmpIndices.sparseBindingFamily.value(), 0, &m_Queues.sparseBindingQueue);
	}
	LogicalDevice::~LogicalDevice()
	{
		vkDestroyDevice(m_LogicalDeviceHandle, nullptr);
	}
}