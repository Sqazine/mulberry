#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include "NonCopyable.h"
#include "VKSurface.h"
namespace mulberry
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamilyIdx;
		std::optional<uint32_t> computeFamilyIdx;
		std::optional<uint32_t> transferFamilyIdx;
		std::optional<uint32_t> presentFamilyIdx;

		bool IsComplete() const
		{
			return graphicsFamilyIdx.has_value() &&
				   computeFamilyIdx.has_value() &&
				   transferFamilyIdx.has_value() &&
				   presentFamilyIdx.has_value();
		}

		bool IsSameFamilyIndex() const
		{
			return graphicsFamilyIdx.value() == computeFamilyIdx.value() && computeFamilyIdx.value() == transferFamilyIdx.value() && transferFamilyIdx.value()==presentFamilyIdx.value();
		}

		std::vector<uint32_t> IndexArray() const
		{
			return {graphicsFamilyIdx.value(), computeFamilyIdx.value(), transferFamilyIdx.value(),presentFamilyIdx.value()};
		}
	};

	struct SwapChainDetails
	{
		std::vector<VkSurfaceFormatKHR> surfaceFormats;
		std::vector<VkPresentModeKHR> presentModes;
		VkSurfaceCapabilitiesKHR surfaceCapabilities;
	};

	struct PhysicalDeviceSpec
	{
		VkPhysicalDevice handle;
		std::vector<VkExtensionProperties> deviceExtensions;
		VkPhysicalDeviceProperties deviceProps;
		VkPhysicalDeviceFeatures features;
		VkPhysicalDeviceMemoryProperties memoryProps;
		std::vector<VkQueueFamilyProperties> queueFamilyProps;
		QueueFamilyIndices queueFamilyIndices;
		SwapChainDetails swapChainDetails;
	};

	class VKAdapter : public NonCopyable
	{
	public:
		VKAdapter();
		~VKAdapter();

		void PrintInstanceInfo();
		void PrintPhysicalDeviceSpecs();

		const VkInstance &GetInstanceHandle() const;
		const std::vector<VkLayerProperties> &GetInstanceLayerProps() const;
		const std::vector<VkExtensionProperties> &GetInstanceExtensionProps() const;

		const VKSurface* GetSurface() const;

		class VKDevice *CreateDevice();

	private:
		void CheckInstanceValidationLayerSupport();
		void CheckInstanceExtensionsSupport();

		void EnumPhysicalDeviceSpecs();

		PhysicalDeviceSpec EnumPhysicalDeviceSpecForHandle(VkPhysicalDevice device);

		std::vector<const char *> mRequiredInstanceExtensions;

		VkInstance mInstanceHandle;
		std::vector<VkLayerProperties> mInstanceLayerProps;
		std::vector<VkExtensionProperties> mInstanceExtensionProps;

#ifdef _DEBUG
		std::vector<const char *> mRequiredValidationLayers =
			{
				"VK_LAYER_KHRONOS_validation",
				"VK_LAYER_LUNARG_monitor"};

		VkDebugUtilsMessengerEXT mDebugMessengerHandle;
#endif

		std::vector<PhysicalDeviceSpec> mPhysicalDeviceSpecs;

		std::unique_ptr<VKSurface> mSurface;
	};
}