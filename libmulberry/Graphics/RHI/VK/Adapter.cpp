#include "Adapter.h"
#include "Logger.h"
#include "Utils.h"
#include "Device.h"
#include "Platform/Window.h"
#include "App.h"

VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
											 VkDebugUtilsMessageTypeFlagsEXT messageType,
											 const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
											 void *pUserData)
{
	std::string tags;

	switch (messageSeverity)
	{
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		tags += "[ERROR]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		tags += "[WARN]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		tags += "[INFO]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		tags += "[VERBOSE]";
		break;
	default:
		break;
	}

	switch (messageType)
	{
	case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
		tags += "[GENERAL]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
		tags += "[VALIDATION]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
		tags += "[PERFORMANCE]";
		break;
	default:
		break;
	}

	switch (pCallbackData->pObjects->objectType)
	{
	case VK_OBJECT_TYPE_INSTANCE:
		tags += "[INSTANCE]";
		break;
	case VK_OBJECT_TYPE_PHYSICAL_DEVICE:
		tags += "[PHYSICAL_DEVICE]";
		break;
	case VK_OBJECT_TYPE_DEVICE:
		tags += "[DEVICE]";
		break;
	case VK_OBJECT_TYPE_QUEUE:
		tags += "[QUEUE]";
		break;
	case VK_OBJECT_TYPE_SEMAPHORE:
		tags += "[SEMAPHORE]";
		break;
	case VK_OBJECT_TYPE_COMMAND_BUFFER:
		tags += "[COMMAND_BUFFER]";
		break;
	case VK_OBJECT_TYPE_FENCE:
		tags += "[FENCE]";
		break;
	case VK_OBJECT_TYPE_DEVICE_MEMORY:
		tags += "[DEVICE_MEMORY]";
		break;
	case VK_OBJECT_TYPE_BUFFER:
		tags += "[BUFFER]";
		break;
	case VK_OBJECT_TYPE_IMAGE:
		tags += "[IMAGE]";
		break;
	case VK_OBJECT_TYPE_EVENT:
		tags += "[EVENT]";
		break;
	case VK_OBJECT_TYPE_QUERY_POOL:
		tags += "[QUERY_POOL]";
		break;
	case VK_OBJECT_TYPE_BUFFER_VIEW:
		tags += "[BUFFER_VIEW]";
		break;
	case VK_OBJECT_TYPE_IMAGE_VIEW:
		tags += "[IMAGE_VIEW]";
		break;
	case VK_OBJECT_TYPE_SHADER_MODULE:
		tags += "[SHADER_MODULE]";
		break;
	case VK_OBJECT_TYPE_PIPELINE_CACHE:
		tags += "[PIPELINE_CACHE]";
		break;
	case VK_OBJECT_TYPE_PIPELINE_LAYOUT:
		tags += "[PIPELINE_LAYOUT]";
		break;
	case VK_OBJECT_TYPE_RENDER_PASS:
		tags += "[RENDER_PASS]";
		break;
	case VK_OBJECT_TYPE_PIPELINE:
		tags += "[PIPELINE]";
		break;
	case VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT:
		tags += "[DESCRIPTOR_SET_LAYOUT]";
		break;
	case VK_OBJECT_TYPE_SAMPLER:
		tags += "[SAMPLER]";
		break;
	case VK_OBJECT_TYPE_DESCRIPTOR_POOL:
		tags += "[DESCRIPTOR_POOL]";
		break;
	case VK_OBJECT_TYPE_DESCRIPTOR_SET:
		tags += "[DESCRIPTOR_SET]";
		break;
	case VK_OBJECT_TYPE_FRAMEBUFFER:
		tags += "[FRAMEBUFFER]";
		break;
	case VK_OBJECT_TYPE_COMMAND_POOL:
		tags += "[COMMAND_POOL]";
		break;
	case VK_OBJECT_TYPE_SURFACE_KHR:
		tags += "[SURFACE_KHR]";
		break;
	case VK_OBJECT_TYPE_SWAPCHAIN_KHR:
		tags += "[SWAPCHAIN_KHR]";
		break;
	case VK_OBJECT_TYPE_DISPLAY_KHR:
		tags += "[DISPLAY_KHR]";
		break;
	case VK_OBJECT_TYPE_DISPLAY_MODE_KHR:
		tags += "[DISPLAY_MODE_KHR]";
		break;
	default:
		break;
	}

	std::cerr << "\033[0m\033[1;31m" << tags << ":" << pCallbackData->pMessage << "\n\033[0m" << std::endl;

	return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(
	VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
	const VkAllocationCallbacks *pAllocator,
	VkDebugUtilsMessengerEXT *pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr)
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	else
		return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr)
		func(instance, debugMessenger, pAllocator);
}
namespace mulberry::vk
{
	Adapter::Adapter()
	{
		CheckInstanceValidationLayerSupport();
		CheckInstanceExtensionsSupport();
		mRequiredInstanceExtensions = App::GetInstance().GetWindow()->GetVulkanRequiredExtensions();

#ifdef _DEBUG
		mRequiredInstanceExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
		debugCreateInfo.pfnUserCallback = DebugCallback;
		debugCreateInfo.pUserData = nullptr;
		debugCreateInfo.flags = 0;
		debugCreateInfo.pNext = nullptr;
#endif

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = nullptr;
		appInfo.applicationVersion = VK_API_VERSION_1_0;
		appInfo.pApplicationName = nullptr;
		appInfo.engineVersion = VK_API_VERSION_1_0;
		appInfo.pEngineName = nullptr;
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.flags = 0;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = mRequiredInstanceExtensions.size();
		createInfo.ppEnabledExtensionNames = mRequiredInstanceExtensions.data();

#ifdef _DEBUG
		createInfo.enabledLayerCount = mRequiredValidationLayers.size();
		createInfo.ppEnabledLayerNames = mRequiredValidationLayers.data();
		createInfo.pNext = &debugCreateInfo;
#else
		createInfo.enabledLayerCount = 0;
		createInfo.ppEnabledLayerNames = nullptr;
		createInfo.pNext = nullptr;
#endif

		VK_CHECK(vkCreateInstance(&createInfo, nullptr, &mInstanceHandle));

#ifdef _DEBUG
		VK_CHECK(CreateDebugUtilsMessengerEXT(mInstanceHandle, &debugCreateInfo, nullptr, &mDebugMessengerHandle))
#endif

		mSurface = App::GetInstance().GetWindow()->CreateVulkanSurface(mInstanceHandle);

		EnumPhysicalDeviceSpecs();
	}
	Adapter::~Adapter()
	{
#ifdef _DEBUG
		DestroyDebugUtilsMessengerEXT(mInstanceHandle, mDebugMessengerHandle, nullptr);
#endif
		vkDestroySurfaceKHR(mInstanceHandle, mSurface, nullptr);

		vkDestroyInstance(mInstanceHandle, nullptr);
	}
	void Adapter::CheckInstanceValidationLayerSupport()
	{
#ifdef _DEBUG
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		mInstanceLayerProps.resize(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, mInstanceLayerProps.data());

		for (const auto &layerName : mRequiredValidationLayers)
		{
			bool layerFound = false;
			for (const auto &layerProperties : mInstanceLayerProps)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}
			if (!layerFound)
				MULBERRY_CORE_ERROR("Not support vulkan instance validation layer:{}", layerName);
		}
#endif
	}
	void Adapter::CheckInstanceExtensionsSupport()
	{
		uint32_t instanceExtensionCount;
		vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, nullptr);
		mInstanceExtensionProps.resize(instanceExtensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, mInstanceExtensionProps.data());

		for (const auto &extName : mRequiredInstanceExtensions)
		{
			bool extFound = false;
			for (const auto &extProperties : mInstanceExtensionProps)
			{
				if (strcmp(extName, extProperties.extensionName) == 0)
				{
					extFound = true;
					break;
				}
			}
			if (!extFound)
				MULBERRY_CORE_ERROR("Not support vulkan instance extension:{}", extName);
		}
	}
	void Adapter::EnumPhysicalDeviceSpecs()
	{
		uint32_t physicalDeviceCount = 0;
		vkEnumeratePhysicalDevices(mInstanceHandle, &physicalDeviceCount, nullptr);
		if (physicalDeviceCount == 0)
			MULBERRY_CORE_ERROR("No GPU support vulkan");

		std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
		vkEnumeratePhysicalDevices(mInstanceHandle, &physicalDeviceCount, physicalDevices.data());

		mPhysicalDeviceSpecs.resize(physicalDeviceCount);
		for (int32_t i = 0; i < physicalDevices.size(); ++i)
			mPhysicalDeviceSpecs[i] = EnumPhysicalDeviceSpecForHandle(physicalDevices[i]);
	}

	PhysicalDeviceSpec Adapter::EnumPhysicalDeviceSpecForHandle(VkPhysicalDevice device)
	{
		PhysicalDeviceSpec result;
		result.handle = device;

		vkGetPhysicalDeviceProperties(device, &result.deviceProps);
		vkGetPhysicalDeviceMemoryProperties(device, &result.memoryProps);
		vkGetPhysicalDeviceFeatures(device, &result.features);

		uint32_t physicalDeviceExtCount = 0;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &physicalDeviceExtCount, nullptr);
		result.deviceExtensions.resize(physicalDeviceExtCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &physicalDeviceExtCount, result.deviceExtensions.data());

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(result.handle, &queueFamilyCount, nullptr);
		result.queueFamilyProps.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(result.handle, &queueFamilyCount, result.queueFamilyProps.data());

		uint32_t i = 0;
		for (const auto &queueFamily : result.queueFamilyProps)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				result.queueFamilyIndices.graphicsFamilyIdx = i;
			if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
				result.queueFamilyIndices.computeFamilyIdx = i;
			if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
				result.queueFamilyIndices.transferFamilyIdx = i;

			VkBool32 surfaceSupported;
			VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(result.handle, i, mSurface, &surfaceSupported));
			if (surfaceSupported)
				result.queueFamilyIndices.presentFamilyIdx = i;

			if (result.queueFamilyIndices.IsComplete())
				break;
			i++;
		}

		return result;
	}
	void Adapter::PrintInstanceInfo()
	{
		MULBERRY_CORE_INFO("Available vulkan instance layers:");
		for (const auto &layerProps : mInstanceLayerProps)
		{
			MULBERRY_CORE_INFO("\tname:{}\n\t\t\tdesc:{}\n\t\t\timplVer:{}.{}.{}\n\t\t\tspecVer:{}.{}.{}",
							   layerProps.layerName,
							   layerProps.description,
							   VK_VERSION_MAJOR(layerProps.implementationVersion),
							   VK_VERSION_MINOR(layerProps.implementationVersion),
							   VK_VERSION_PATCH(layerProps.implementationVersion),
							   VK_VERSION_MAJOR(layerProps.specVersion),
							   VK_VERSION_MINOR(layerProps.specVersion),
							   VK_VERSION_PATCH(layerProps.specVersion));
		}

		MULBERRY_CORE_INFO("Available vulkan instance extensions:");
		for (const auto &extensionProps : mInstanceExtensionProps)
		{
			MULBERRY_CORE_INFO("\tname:{}\n\t\t\tspecVer:{}.{}.{}", extensionProps.extensionName,
							   VK_VERSION_MAJOR(extensionProps.specVersion),
							   VK_VERSION_MINOR(extensionProps.specVersion),
							   VK_VERSION_PATCH(extensionProps.specVersion));
		}
	}
	void Adapter::PrintPhysicalDeviceSpecs()
	{
		MULBERRY_CORE_INFO("Available vulkan physical devices:");
		for (const auto &spec : mPhysicalDeviceSpecs)
		{

			MULBERRY_CORE_INFO("\tDevice: ");
			MULBERRY_CORE_INFO("\t\tname:{}", spec.deviceProps.deviceName);

			switch (spec.deviceProps.deviceType)
			{
			case VK_PHYSICAL_DEVICE_TYPE_OTHER:
				MULBERRY_CORE_INFO("\t\ttype:Unknown device.");
				break;
			case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
				MULBERRY_CORE_INFO("\t\ttype:Integrate GPU");
				break;
			case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
				MULBERRY_CORE_INFO("\t\ttype:Discrete GPU");
				break;
			case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
				MULBERRY_CORE_INFO("\t\ttype:Virtual GPU");
				break;
			case VK_PHYSICAL_DEVICE_TYPE_CPU:
				MULBERRY_CORE_INFO("\t\ttype:CPU");
				break;
			default:;
			}

			MULBERRY_CORE_INFO("\t\tdriver version:{}.{}.{}", VK_VERSION_MAJOR(spec.deviceProps.driverVersion), VK_VERSION_MINOR(spec.deviceProps.driverVersion), VK_VERSION_PATCH(spec.deviceProps.driverVersion));
			MULBERRY_CORE_INFO("\t\tvulkan api version:{}.{}.{}", VK_VERSION_MAJOR(spec.deviceProps.apiVersion), VK_VERSION_MINOR(spec.deviceProps.apiVersion), VK_VERSION_PATCH(spec.deviceProps.apiVersion));
		}
	}
	const VkInstance &Adapter::GetInstanceHandle() const
	{
		return mInstanceHandle;
	}
	const std::vector<VkLayerProperties> &Adapter::GetInstanceLayerProps() const
	{
		return mInstanceLayerProps;
	}
	const std::vector<VkExtensionProperties> &Adapter::GetInstanceExtensionProps() const
	{
		return mInstanceExtensionProps;
	}

	const VkSurfaceKHR Adapter::GetSurface() const
	{
		return mSurface;
	}

	Device *Adapter::CreateDevice()
	{
		auto idx = 0;
		for (idx = 0; idx < mPhysicalDeviceSpecs.size(); ++idx)
		{
			bool isFound = false;
			for (const auto &requiredDeviceExt : mRequiredDeviceExtensions)
			{
				int32_t isSatisfied = 0;
				for (int32_t i = 0; i < mPhysicalDeviceSpecs[idx].deviceExtensions.size(); ++i)
				{
					if (mPhysicalDeviceSpecs[idx].deviceExtensions[i].extensionName == requiredDeviceExt)
						isSatisfied++;
				}
				if (isSatisfied == mRequiredDeviceExtensions.size() - 1)
					isFound = true;
			}

			if (isFound)
				break;
		}

		return new Device(mPhysicalDeviceSpecs[idx], mRequiredDeviceExtensions);
	}
}