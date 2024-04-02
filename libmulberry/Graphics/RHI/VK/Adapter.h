#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include "Core/NonCopyable.h"
namespace mulberry::vk
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
			return graphicsFamilyIdx.value() == computeFamilyIdx.value() && computeFamilyIdx.value() == transferFamilyIdx.value() && transferFamilyIdx.value() == presentFamilyIdx.value();
		}

		std::vector<uint32_t> IndexArray() const
		{
			return {graphicsFamilyIdx.value(), computeFamilyIdx.value(), transferFamilyIdx.value(), presentFamilyIdx.value()};
		}
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
	};

	class Adapter : public NonCopyable
	{
	public:
		Adapter();
		~Adapter();

		void PrintInstanceInfo();
		void PrintPhysicalDeviceSpecs();

		const VkInstance &GetInstanceHandle() const;
		const std::vector<VkLayerProperties> &GetInstanceLayerProps() const;
		const std::vector<VkExtensionProperties> &GetInstanceExtensionProps() const;

		const VkSurfaceKHR GetSurface() const;

		class Device *CreateDevice();

	private:
		void CheckInstanceValidationLayerSupport();
		void CheckInstanceExtensionsSupport();

		void EnumPhysicalDeviceSpecs();

		PhysicalDeviceSpec EnumPhysicalDeviceSpecForHandle(VkPhysicalDevice device);

		std::vector<const char *> mRequiredInstanceExtensions{};

		VkInstance mInstanceHandle{VK_NULL_HANDLE};
		std::vector<VkLayerProperties> mInstanceLayerProps{};
		std::vector<VkExtensionProperties> mInstanceExtensionProps{};

#ifdef _DEBUG
		std::vector<const char *> mRequiredValidationLayers =
			{
				"VK_LAYER_KHRONOS_validation",
			};

		VkDebugUtilsMessengerEXT mDebugMessengerHandle;
#endif

		std::vector<const char *> mRequiredDeviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME};

		std::vector<PhysicalDeviceSpec> mPhysicalDeviceSpecs;

		VkSurfaceKHR mSurface{VK_NULL_HANDLE};
	};
}