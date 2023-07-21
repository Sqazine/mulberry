#include "Shader.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include "Utils.h"
#include "Device.h"
#include "Context.h"

namespace mulberry::vk 
{
	Shader::Shader(ShaderType type, std::string_view content)
	{
		std::vector<uint32_t> pCode=GlslToSpv((VkShaderStageFlagBits)type, content);
	
		VkShaderModuleCreateInfo info;
		info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.flags = 0;
		info.pNext = nullptr;
		info.codeSize = pCode.size() * sizeof(uint32_t);
		info.pCode = pCode.data();

		VK_CHECK(vkCreateShaderModule(Context::GetInstance().GetDevice()->GetHandle(), &info, nullptr, &mShaderModule));

		mStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		mStageCreateInfo.pNext = nullptr;
		mStageCreateInfo.flags = 0;
		mStageCreateInfo.stage = (VkShaderStageFlagBits)type;
		mStageCreateInfo.module = mShaderModule;
		mStageCreateInfo.pName = "main";
		mStageCreateInfo.pSpecializationInfo = nullptr;
	}
	Shader::~Shader()
	{
		vkDestroyShaderModule(Context::GetInstance().GetDevice()->GetHandle(), mShaderModule, nullptr);
	}

	const VkPipelineShaderStageCreateInfo& Shader::GetStageCreateInfo() const
	{
		return mStageCreateInfo;
	}

	const VkShaderModule& Shader::GetHandle() const
	{
		return mShaderModule;
	}
}