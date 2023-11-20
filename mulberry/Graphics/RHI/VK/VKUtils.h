#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include <iostream>
#include <cassert>
#include "VKQueue.h"

namespace mulberry
{
	inline const char *GetErrorCode(const VkResult result)
	{
		switch (result)
		{
#define STR(r)   \
	case VK_##r: \
		return #r
			STR(SUCCESS);
			STR(NOT_READY);
			STR(TIMEOUT);
			STR(EVENT_SET);
			STR(EVENT_RESET);
			STR(INCOMPLETE);
			STR(ERROR_OUT_OF_HOST_MEMORY);
			STR(ERROR_OUT_OF_DEVICE_MEMORY);
			STR(ERROR_INITIALIZATION_FAILED);
			STR(ERROR_DEVICE_LOST);
			STR(ERROR_MEMORY_MAP_FAILED);
			STR(ERROR_LAYER_NOT_PRESENT);
			STR(ERROR_EXTENSION_NOT_PRESENT);
			STR(ERROR_FEATURE_NOT_PRESENT);
			STR(ERROR_INCOMPATIBLE_DRIVER);
			STR(ERROR_TOO_MANY_OBJECTS);
			STR(ERROR_FORMAT_NOT_SUPPORTED);
			STR(ERROR_FRAGMENTED_POOL);
			STR(ERROR_OUT_OF_POOL_MEMORY);
			STR(ERROR_INVALID_EXTERNAL_HANDLE);
			STR(ERROR_SURFACE_LOST_KHR);
			STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
			STR(SUBOPTIMAL_KHR);
			STR(ERROR_OUT_OF_DATE_KHR);
			STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
			STR(ERROR_VALIDATION_FAILED_EXT);
			STR(ERROR_INVALID_SHADER_NV);
			STR(ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
			STR(ERROR_FRAGMENTATION_EXT);
			STR(ERROR_NOT_PERMITTED_EXT);
			STR(ERROR_INVALID_DEVICE_ADDRESS_EXT);
#undef STR
		default:
			return "UNKNOWN_ERROR";
		}
	}

#ifdef _DEBUG
#define VK_CHECK(x)                                                                            \
	do                                                                                         \
	{                                                                                          \
		VkResult err = (x);                                                                    \
		if (err)                                                                               \
			MULBERRY_CORE_ERROR("[ERROR]:[{}]{} {}\n", GetErrorCode(err), __FILE__, __LINE__); \
	} while (0);
#else
#define VK_CHECK(x) (x);
#endif

#define VK_CONTEXT (App::GetInstance().GetGraphicsContext()->GetVKContext())
#define RAW_VK_DEVICE_HANDLE (VK_CONTEXT->GetDevice()->GetHandle())

#define RESOLVE_VK_INSTANCE_PFN(instance, funcName)                                                 \
	{                                                                                               \
		funcName = reinterpret_cast<PFN_##funcName>(vkGetInstanceProcAddr(instance, "" #funcName)); \
		if (funcName == nullptr)                                                                    \
			MULBERRY_CORE_ERROR("Failed to resolve function:{}\n", #funcName);                      \
	}

#define RESOLVE_VK_DEVICE_PFN(device, funcName)                                                 \
	{                                                                                           \
		funcName = reinterpret_cast<PFN_##funcName>(vkGetDeviceProcAddr(device, "" #funcName)); \
		if (funcName == nullptr)                                                                \
			MULBERRY_CORE_ERROR("Failed to resolve function:{}\n", #funcName);                  \
	}
}

namespace mulberry
{
	struct SwapChainDetails
	{
		std::vector<VkSurfaceFormatKHR> surfaceFormats;
		std::vector<VkPresentModeKHR> presentModes;
		VkSurfaceCapabilitiesKHR surfaceCapabilities;
	};

	bool HasStencilComponent(VkFormat format);

	std::vector<uint32_t> GlslToSpv(const VkShaderStageFlagBits shaderStage, std::string_view shaderSrc);

	uint32_t GetBiggerTwoPower(uint32_t val);

	VkShaderStageFlagBits ToVkShaderStage(enum class ShaderStage type);

	std::string ToVKShaderSourceCode(std::string_view src);
}