#include "VKShader.h"
#include <fstream>
#include <sstream>
#include "Logger.h"
#include "VKUtils.h"
#include "VKDevice.h"
#include "VKContext.h"

namespace mulberry
{
	VKShaderModule::VKShaderModule(ShaderType type, std::string_view content)
	{
		auto nativeVkShaderType = ToVkShaderType(type);

		std::vector<uint32_t> pCode = GlslToSpv(nativeVkShaderType, content);

		VkShaderModuleCreateInfo info;
		info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.flags = 0;
		info.pNext = nullptr;
		info.codeSize = pCode.size() * sizeof(uint32_t);
		info.pCode = pCode.data();

		VK_CHECK(vkCreateShaderModule(VKContext::GetInstance().GetDevice()->GetHandle(), &info, nullptr, &mShaderModule));

		mStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		mStageCreateInfo.pNext = nullptr;
		mStageCreateInfo.flags = 0;
		mStageCreateInfo.stage = nativeVkShaderType;
		mStageCreateInfo.module = mShaderModule;
		mStageCreateInfo.pName = "main";
		mStageCreateInfo.pSpecializationInfo = nullptr;
	}

	VKShaderModule::~VKShaderModule()
	{
		vkDestroyShaderModule(VKContext::GetInstance().GetDevice()->GetHandle(), mShaderModule, nullptr);
	}

	const VkPipelineShaderStageCreateInfo &VKShaderModule::GetStageCreateInfo() const
	{
		return mStageCreateInfo;
	}

	const VkShaderModule &VKShaderModule::GetHandle() const
	{
		return mShaderModule;
	}
}