#include "Shader.h"
#include "Utils.h"
#include "Context.h"
#include "Device.h"
namespace VK
{
	ShaderModule::ShaderModule()
		: m_ShaderModuleHandle(VK_NULL_HANDLE)
	{
	}
	ShaderModule::~ShaderModule()
	{
		vkDestroyShaderModule(Context::m_LogicalDevice.get()->m_LogicalDeviceHandle, m_ShaderModuleHandle, nullptr);
	}

	bool CompileSource(const ShaderModuleType& type, std::string_view content)
	{
		return true;
	}

	bool ShaderModule::CompileBinary(const ShaderModuleType& type, std::string_view content)
	{
		m_Type = type;
		VkShaderModuleCreateInfo createInfo =
		{
			.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.codeSize = content.size(),
			.pCode = (uint32_t*)content.data(),
		};

		VK_CHECK_RESULT(vkCreateShaderModule(Context::m_LogicalDevice.get()->m_LogicalDeviceHandle, &createInfo, nullptr, &m_ShaderModuleHandle));

		m_ShaderStageCreateInfo =
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.stage = (VkShaderStageFlagBits)type,
			.module = m_ShaderModuleHandle,
			.pName = "main",
			.pSpecializationInfo = nullptr,
		};

		return true;
	}

	const ShaderModuleType& ShaderModule::Type() const
	{
		return m_Type;
	}
}