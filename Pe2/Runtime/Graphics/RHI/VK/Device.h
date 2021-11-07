#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include <cstdint>
#include <array>
#include <optional>
#include <string_view>


namespace VK
{

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		std::optional<uint32_t> computeFamily;
		std::optional<uint32_t> transferFamily;
		std::optional<uint32_t> sparseBindingFamily;
	};

	struct Queues
	{
		VkQueue graphicsQueue;
		VkQueue presentQueue;
		VkQueue computeQueue;
		VkQueue transferQueue;
		VkQueue sparseBindingQueue;
	};

	struct SwapChainDetails
	{
		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		std::vector<VkSurfaceFormatKHR> surfaceFormats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class PhysicalDevice 
	{
	public:
		PhysicalDevice();
		~PhysicalDevice();

		bool IsExtensionSupport(std::string_view extName);
		bool IsLayerSupport(std::string_view layerName);

	private:
		friend class Context;
		friend class PhysicalDeviceList;
		friend class LogicalDevice;
		friend class SwapChain;

		VkPhysicalDevice m_PhysicalDeviceHandle;
		VkPhysicalDeviceProperties m_PhysicalDeviceProps;
		VkPhysicalDeviceFeatures m_PhysicalDeviceFeatures;
		VkPhysicalDeviceMemoryProperties m_PhysicalDeviceMemoryProps;
		std::vector<VkQueueFamilyProperties> m_PhysicalDeviceQueueFamilyProps;

		std::vector<VkExtensionProperties> m_PhysicalDeviceExtensionProps;
		std::vector<VkLayerProperties> m_PhysicalDeviceLayerProps;

		SwapChainDetails m_SwapChainDetails;
		QueueFamilyIndices m_QueueFamilyIndices;
	};

	class PhysicalDeviceList 
	{
	public:
		PhysicalDeviceList();
		~PhysicalDeviceList();

		PhysicalDevice GetSuitablePhysicalDevice();

	private:
		uint32_t m_BestPhysicalDeviceIdx;
		
		friend class Context;
		friend class Instance;
		friend class SwapChain;

		void EnumeratePhysicalDevices();
		void EnumeratePhysicalDeviceProps();
		void EnumeratePhysicalDeviceFeatures();
		void EnumeratePhysicalDeviceExtensions();
		void EnumeratePhysicalDeviceLayerProps();
		void EnumeratePhysicalDeviceMemoryProps();
		void EnumeratePhysicalDeviceQueueFamilyProps();
		void EnumeratePhysicalDeviceQueueFamilies();

		void EnumeratePhysicalDeviceSwapChainDetails();

		std::vector<PhysicalDevice> m_PhysicalDeviceList;

	};

	class LogicalDevice 
	{
	public:
		LogicalDevice();
		~LogicalDevice();

	private:
		friend class SwapChain;
		friend class ShaderModule;

		VkDevice m_LogicalDeviceHandle;
		Queues m_Queues;
	};

}