#include "Shader.h"
#include <fstream>
#include <sstream>
#include "Logger.h"
#include "Utils.h"
#include "Device.h"

namespace mulberry::vk
{
	Shader::Shader(ShaderStage type, std::string_view content)
		: mType(type)
	{
		auto sourceCode = ToShaderSourceCode(content);

		std::vector<uint32_t> pCode = GlslToSpv(SHADER_STAGE_CAST(type), sourceCode.data());

		VkShaderModuleCreateInfo info;
		info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.flags = 0;
		info.pNext = nullptr;
		info.codeSize = pCode.size() * sizeof(uint32_t);
		info.pCode = pCode.data();

		VK_CHECK(vkCreateShaderModule(mDevice.GetHandle(), &info, nullptr, &mShader));

		mStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		mStageCreateInfo.pNext = nullptr;
		mStageCreateInfo.flags = 0;
		mStageCreateInfo.stage = SHADER_STAGE_CAST(type);
		mStageCreateInfo.module = mShader;
		mStageCreateInfo.pName = "main";
		mStageCreateInfo.pSpecializationInfo = nullptr;
	}

	Shader::~Shader()
	{
		vkDestroyShaderModule(mDevice.GetHandle(), mShader, nullptr);
	}

	const VkPipelineShaderStageCreateInfo &Shader::GetStageCreateInfo() const
	{
		return mStageCreateInfo;
	}

	const VkShaderModule &Shader::GetHandle() const
	{
		return mShader;
	}

	const ShaderStage &Shader::Type() const
	{
		return mType;
	}

	std::vector<VkPipelineShaderStageCreateInfo> RasterShaderGroup::GetShaderStages()
	{
		if (!mVertShader)
			MULBERRY_CORE_ERROR("Vertex shader is necessary in rasterization");

		if (!mFragShader)
			MULBERRY_CORE_ERROR("Fragment shader is necessary in rasterization");

		std::vector<VkPipelineShaderStageCreateInfo> result;

		result.emplace_back(mVertShader->GetStageCreateInfo());

		if (mTesslCtrlShader && mTesslEvalShader)
		{
			result.emplace_back(mTesslCtrlShader->GetStageCreateInfo());
			result.emplace_back(mTesslEvalShader->GetStageCreateInfo());
		}
		else if (mTesslCtrlShader)
			MULBERRY_CORE_ERROR("Tessellation Evaluation shader is necessary in rasterization while existing Tessellation Control Shader")
		else if (mTesslEvalShader)
			MULBERRY_CORE_ERROR("Tessellation Control shader is necessary in rasterization while existing Tessellation Evaluation Shader")

		if (mGeomShader)
			result.emplace_back(mGeomShader->GetStageCreateInfo());

		result.emplace_back(mFragShader->GetStageCreateInfo());

		return result;
	}

	void RasterShaderGroup::SetVertexShader(Shader *shader)
	{
		mVertShader.reset(shader);
	}
	void RasterShaderGroup::SetTessellationControlShader(Shader *shader)
	{
		mTesslCtrlShader.reset(shader);
	}
	void RasterShaderGroup::SetTessellationEvaluationShader(Shader *shader)
	{
		mTesslEvalShader.reset(shader);
	}
	void RasterShaderGroup::SetGeometryShader(Shader *shader)
	{
		mGeomShader.reset(shader);
	}
	void RasterShaderGroup::SetFragmentShader(Shader *shader)
	{
		mFragShader.reset(shader);
	}

	uint32_t RasterShaderGroup::GetAttribute(std::string_view name) const
	{
		return 0;
	}
	uint32_t RasterShaderGroup::GetUniform(std::string_view name) const
	{
		return 0;
	}

	void ComputeShaderGroup::SetShader(Shader* shader)
	{
		mCompShader.reset(shader);
	}

	const VkPipelineShaderStageCreateInfo& ComputeShaderGroup::GetShaderStage() const
	{
		return mCompShader->GetStageCreateInfo();
	}

	uint32_t ComputeShaderGroup::GetAttribute(std::string_view name) const
	{
		return 0;
	}

	uint32_t ComputeShaderGroup::GetUniform(std::string_view name) const
	{
		return 0;
	}

}