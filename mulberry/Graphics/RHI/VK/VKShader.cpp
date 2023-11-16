#include "VKShader.h"
#include <fstream>
#include <sstream>
#include "Logger.h"
#include "VKUtils.h"
#include "VKDevice.h"
#include "VKContext.h"
#include "App.h"

namespace mulberry
{
	VKShader::VKShader(ShaderStage type, std::string_view content)
		: mType(type)
	{
		auto nativeVkShaderModuleStage = ToVkShaderStage(type);

		auto sourceCode = ToVKShaderSourceCode(content);

		std::vector<uint32_t> pCode = GlslToSpv(nativeVkShaderModuleStage, sourceCode.data());

		VkShaderModuleCreateInfo info;
		info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.flags = 0;
		info.pNext = nullptr;
		info.codeSize = pCode.size() * sizeof(uint32_t);
		info.pCode = pCode.data();

		VK_CHECK(vkCreateShaderModule(App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->GetHandle(), &info, nullptr, &mShader));

		mStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		mStageCreateInfo.pNext = nullptr;
		mStageCreateInfo.flags = 0;
		mStageCreateInfo.stage = nativeVkShaderModuleStage;
		mStageCreateInfo.module = mShader;
		mStageCreateInfo.pName = "main";
		mStageCreateInfo.pSpecializationInfo = nullptr;
	}

	VKShader::~VKShader()
	{
		vkDestroyShaderModule(App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->GetHandle(), mShader, nullptr);
	}

	const VkPipelineShaderStageCreateInfo &VKShader::GetStageCreateInfo() const
	{
		return mStageCreateInfo;
	}

	const VkShaderModule &VKShader::GetHandle() const
	{
		return mShader;
	}

	const ShaderStage &VKShader::Type() const
	{
		return mType;
	}
}