#pragma once
#include <vulkan/vulkan.h>
#include <string_view>
#include "Graphics/Shader.h"
namespace mulberry 
{
	class VKShaderModule
	{
	public:
		VKShaderModule(ShaderType type, std::string_view content);
		~VKShaderModule();

		const VkPipelineShaderStageCreateInfo& GetStageCreateInfo() const;
		const VkShaderModule& GetHandle() const;

	private:
		VkShaderModule mShaderModule;
		VkPipelineShaderStageCreateInfo mStageCreateInfo;
	};
}