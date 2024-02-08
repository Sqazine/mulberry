#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include <string_view>
#include <vector>
#include "Object.h"
#include "../Enum.h"
namespace mulberry::rhi::vk
{
	class Shader:public Object
	{
	public:
		Shader(ShaderStage type, std::string_view content);
		~Shader();

		const VkPipelineShaderStageCreateInfo &GetStageCreateInfo() const;
		const VkShaderModule &GetHandle() const;

		const ShaderStage &Type() const;
	private:
		ShaderStage mType;
		VkShaderModule mShader;
		VkPipelineShaderStageCreateInfo mStageCreateInfo;
	};

	class RasterShaderGroup
	{
	public:
		void SetVertexShader(Shader *shader);
		void SetTessellationControlShader(Shader *shader);
		void SetTessellationEvaluationShader(Shader *shader);
		void SetGeometryShader(Shader *shader);
		void SetFragmentShader(Shader *shader);

		std::vector<VkPipelineShaderStageCreateInfo> GetShaderStages();

		uint32_t GetAttribute(std::string_view name) const;
		uint32_t GetUniform(std::string_view name) const;

	private:
		std::unique_ptr<Shader> mVertShader;
		std::unique_ptr<Shader> mTesslCtrlShader;
		std::unique_ptr<Shader> mTesslEvalShader;
		std::unique_ptr<Shader> mGeomShader;
		std::unique_ptr<Shader> mFragShader;
	};

	class ComputeShaderGroup
	{
	public:
		void SetShader(Shader *shader);

		const VkPipelineShaderStageCreateInfo& GetShaderStage() const;

		uint32_t GetAttribute(std::string_view name) const;
		uint32_t GetUniform(std::string_view name) const;
	private:
		std::unique_ptr<Shader> mCompShader;
	};
}