#pragma once
#include <vulkan/vulkan.h>
#include <string_view>
#include "Graphics/RHI/Shader.h"
namespace mulberry
{
	class VKShader
	{
	public:
		VKShader(ShaderStage type, std::string_view content);
		~VKShader();

		const VkPipelineShaderStageCreateInfo &GetStageCreateInfo() const;
		const VkShaderModule &GetHandle() const;

		const ShaderStage &Type() const;

	private:
		ShaderStage mType;
		VkShaderModule mShader;
		VkPipelineShaderStageCreateInfo mStageCreateInfo;
	};

	class VKShaderGroup
	{
	public:
		void SetVertexShader(VKShader *shader);
		void SetTessellationControlShader(VKShader *shader);
		void SetTessellationEvaluationShader(VKShader *shader);
		void SetGeometryShader(VKShader *shader);
		void SetFragmentShader(VKShader *shader);

		std::vector<VkPipelineShaderStageCreateInfo> GetShaderStages();

	private:
	};
}