#pragma once
#include <vulkan/vulkan.h>
#include <string_view>
#include "Graphics/RHI/Shader.h"
namespace mulberry
{
	class VKShaderModule
	{
	public:
		VKShaderModule(ShaderStage type, std::string_view content);
		~VKShaderModule();

		const VkPipelineShaderStageCreateInfo &GetStageCreateInfo() const;
		const VkShaderModule &GetHandle() const;

		const ShaderStage &Type() const;

	private:
		ShaderStage mType;
		VkShaderModule mShaderModule;
		VkPipelineShaderStageCreateInfo mStageCreateInfo;
	};

	class VKShaderProgram
	{
		
	};
}