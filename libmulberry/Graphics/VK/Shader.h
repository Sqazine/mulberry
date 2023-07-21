#pragma once
#include <vulkan/vulkan.h>
#include <string_view>
namespace mulberry::vk 
{
	enum ShaderType
	{
		VERTEX = VK_SHADER_STAGE_VERTEX_BIT,
		FRAGMENT = VK_SHADER_STAGE_FRAGMENT_BIT,
		COMPUTE = VK_SHADER_STAGE_COMPUTE_BIT,
	};

	class Shader
	{
	public:
		Shader(ShaderType type, std::string_view content);
		~Shader();

		const VkPipelineShaderStageCreateInfo& GetStageCreateInfo() const;
		const VkShaderModule& GetHandle() const;

	private:
		VkShaderModule mShaderModule;
		VkPipelineShaderStageCreateInfo mStageCreateInfo;
	};
}