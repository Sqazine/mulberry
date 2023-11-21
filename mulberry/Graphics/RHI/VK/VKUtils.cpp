#include "VKUtils.h"
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include "Logger.h"
#include "Graphics/RHI/Shader.h"
#include "Graphics/RHI/Texture.h"
#include "Platform/IO.h"
namespace mulberry
{
	bool HasStencilComponent(VkFormat format)
	{
		return format == VK_FORMAT_D32_SFLOAT_S8_UINT ||
			   format == VK_FORMAT_D24_UNORM_S8_UINT ||
			   format == VK_FORMAT_D16_UNORM_S8_UINT ||
			   format == VK_FORMAT_S8_UINT;
	}

	static TBuiltInResource InitResources() noexcept
	{
		TBuiltInResource resources{};

		resources.maxLights = 32;
		resources.maxClipPlanes = 6;
		resources.maxTextureUnits = 32;
		resources.maxTextureCoords = 32;
		resources.maxVertexAttribs = 64;
		resources.maxVertexUniformComponents = 4096;
		resources.maxVaryingFloats = 64;
		resources.maxVertexTextureImageUnits = 32;
		resources.maxCombinedTextureImageUnits = 80;
		resources.maxTextureImageUnits = 32;
		resources.maxFragmentUniformComponents = 4096;
		resources.maxDrawBuffers = 32;
		resources.maxVertexUniformVectors = 128;
		resources.maxVaryingVectors = 8;
		resources.maxFragmentUniformVectors = 16;
		resources.maxVertexOutputVectors = 16;
		resources.maxFragmentInputVectors = 15;
		resources.minProgramTexelOffset = -8;
		resources.maxProgramTexelOffset = 7;
		resources.maxClipDistances = 8;
		resources.maxComputeWorkGroupCountX = 65535;
		resources.maxComputeWorkGroupCountY = 65535;
		resources.maxComputeWorkGroupCountZ = 65535;
		resources.maxComputeWorkGroupSizeX = 1024;
		resources.maxComputeWorkGroupSizeY = 1024;
		resources.maxComputeWorkGroupSizeZ = 64;
		resources.maxComputeUniformComponents = 1024;
		resources.maxComputeTextureImageUnits = 16;
		resources.maxComputeImageUniforms = 8;
		resources.maxComputeAtomicCounters = 8;
		resources.maxComputeAtomicCounterBuffers = 1;
		resources.maxVaryingComponents = 60;
		resources.maxVertexOutputComponents = 64;
		resources.maxGeometryInputComponents = 64;
		resources.maxGeometryOutputComponents = 128;
		resources.maxFragmentInputComponents = 128;
		resources.maxImageUnits = 8;
		resources.maxCombinedImageUnitsAndFragmentOutputs = 8;
		resources.maxCombinedShaderOutputResources = 8;
		resources.maxImageSamples = 0;
		resources.maxVertexImageUniforms = 0;
		resources.maxTessControlImageUniforms = 0;
		resources.maxTessEvaluationImageUniforms = 0;
		resources.maxGeometryImageUniforms = 0;
		resources.maxFragmentImageUniforms = 8;
		resources.maxCombinedImageUniforms = 8;
		resources.maxGeometryTextureImageUnits = 16;
		resources.maxGeometryOutputVertices = 256;
		resources.maxGeometryTotalOutputComponents = 1024;
		resources.maxGeometryUniformComponents = 1024;
		resources.maxGeometryVaryingComponents = 64;
		resources.maxTessControlInputComponents = 128;
		resources.maxTessControlOutputComponents = 128;
		resources.maxTessControlTextureImageUnits = 16;
		resources.maxTessControlUniformComponents = 1024;
		resources.maxTessControlTotalOutputComponents = 4096;
		resources.maxTessEvaluationInputComponents = 128;
		resources.maxTessEvaluationOutputComponents = 128;
		resources.maxTessEvaluationTextureImageUnits = 16;
		resources.maxTessEvaluationUniformComponents = 1024;
		resources.maxTessPatchComponents = 120;
		resources.maxPatchVertices = 32;
		resources.maxTessGenLevel = 64;
		resources.maxViewports = 16;
		resources.maxVertexAtomicCounters = 0;
		resources.maxTessControlAtomicCounters = 0;
		resources.maxTessEvaluationAtomicCounters = 0;
		resources.maxGeometryAtomicCounters = 0;
		resources.maxFragmentAtomicCounters = 8;
		resources.maxCombinedAtomicCounters = 8;
		resources.maxAtomicCounterBindings = 1;
		resources.maxVertexAtomicCounterBuffers = 0;
		resources.maxTessControlAtomicCounterBuffers = 0;
		resources.maxTessEvaluationAtomicCounterBuffers = 0;
		resources.maxGeometryAtomicCounterBuffers = 0;
		resources.maxFragmentAtomicCounterBuffers = 1;
		resources.maxCombinedAtomicCounterBuffers = 1;
		resources.maxAtomicCounterBufferSize = 16384;
		resources.maxTransformFeedbackBuffers = 4;
		resources.maxTransformFeedbackInterleavedComponents = 64;
		resources.maxCullDistances = 8;
		resources.maxCombinedClipAndCullDistances = 8;
		resources.maxSamples = 4;
		resources.maxMeshOutputVerticesNV = 256;
		resources.maxMeshOutputPrimitivesNV = 512;
		resources.maxMeshWorkGroupSizeX_NV = 32;
		resources.maxMeshWorkGroupSizeY_NV = 1;
		resources.maxMeshWorkGroupSizeZ_NV = 1;
		resources.maxTaskWorkGroupSizeX_NV = 32;
		resources.maxTaskWorkGroupSizeY_NV = 1;
		resources.maxTaskWorkGroupSizeZ_NV = 1;
		resources.maxMeshViewCountNV = 4;

		resources.limits.nonInductiveForLoops = 1;
		resources.limits.whileLoops = 1;
		resources.limits.doWhileLoops = 1;
		resources.limits.generalUniformIndexing = 1;
		resources.limits.generalAttributeMatrixVectorIndexing = 1;
		resources.limits.generalVaryingIndexing = 1;
		resources.limits.generalSamplerIndexing = 1;
		resources.limits.generalVariableIndexing = 1;
		resources.limits.generalConstantMatrixVectorIndexing = 1;

		return resources;
	}

	std::vector<uint32_t> GlslToSpv(const VkShaderStageFlagBits shaderStage, std::string_view shaderSrc)
	{
		glslang::InitializeProcess();

		glslang::TProgram program;

		EShLanguage stage;
		switch (shaderStage)
		{
		case VK_SHADER_STAGE_VERTEX_BIT:
			stage = EShLangVertex;
			break;
		case VK_SHADER_STAGE_FRAGMENT_BIT:
			stage = EShLangFragment;
			break;
		default:
			stage = EShLangMiss;
			break;
		}

		glslang::TShader *shader = new glslang::TShader(stage);

		std::vector<const char *> pTempShaderSrc{shaderSrc.data()};
		shader->setStrings(pTempShaderSrc.data(), static_cast<int>(pTempShaderSrc.size()));
		shader->setEnvInput(glslang::EShSource::EShSourceGlsl, stage, glslang::EShClient::EShClientVulkan, glslang::EShTargetClientVersion::EShTargetVulkan_1_2);
		shader->setEnvClient(glslang::EShClient::EShClientVulkan, glslang::EShTargetClientVersion::EShTargetVulkan_1_2);
		shader->setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_0);

		EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);

		TBuiltInResource resource = InitResources();

		if (!shader->parse(&resource, 450, false, messages))
		{
			std::cout << shader->getInfoLog() << std::endl;
			std::cout << shader->getInfoDebugLog() << std::endl;
			return {};
		}

		program.addShader(shader);

		if (!program.link(messages))
		{
			std::cout << program.getInfoLog() << std::endl;
			std::cout << program.getInfoDebugLog() << std::endl;
			return {};
		}

		std::vector<uint32_t> result;

		glslang::GlslangToSpv(*program.getIntermediate(stage), result);

		glslang::FinalizeProcess();

		delete shader;

		return result;
	}

	uint32_t GetBiggerTwoPower(uint32_t val)
	{
		if (val & (val - 1))
		{
			val |= val >> 1;
			val |= val >> 2;
			val |= val >> 4;
			val |= val >> 8;
			val |= val >> 16;
			return val + 1;
		}
		else
			return val == 0 ? 1 : val;
	}

	VkShaderStageFlagBits ToVkShaderStage(ShaderStage type)
	{
		switch (type)
		{
		case ShaderStage::VERTEX:
			return VK_SHADER_STAGE_VERTEX_BIT;
		case ShaderStage::FRAGMENT:
			return VK_SHADER_STAGE_FRAGMENT_BIT;
		case ShaderStage::GEOMETRY:
			return VK_SHADER_STAGE_GEOMETRY_BIT;
		case ShaderStage::COMPUTE:
			return VK_SHADER_STAGE_COMPUTE_BIT;
		case ShaderStage::TESS_CTRL:
			return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		case ShaderStage::TESS_EVAL:
			return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		default:
			return VK_SHADER_STAGE_VERTEX_BIT;
		}
	}

	VkFormat ToVkFormat(Format format)
	{
		switch (format)
		{
		case Format::R8:
			return VK_FORMAT_R8_UNORM;
		case Format::RG8:
			return VK_FORMAT_R8G8_UNORM;
		case Format::RGB8:
			return VK_FORMAT_R8G8B8_UNORM;
		case Format::RGBA8:
			return VK_FORMAT_R8G8B8A8_UNORM;
		case Format::R16F:
			return VK_FORMAT_R16_SFLOAT;
		case Format::RG16F:
			return VK_FORMAT_R16G16_SFLOAT;
		case Format::RGB16F:
			return VK_FORMAT_R16G16B16_SFLOAT;
		case Format::RGBA16F:
			return VK_FORMAT_R16G16B16A16_SFLOAT;
		case Format::R32F:
			return VK_FORMAT_R32_SFLOAT;
		case Format::RG32F:
			return VK_FORMAT_R32G32_SFLOAT;
		case Format::RGB32F:
			return VK_FORMAT_R32G32B32_SFLOAT;
		case Format::RGBA32F:
			return VK_FORMAT_R32G32B32A32_SFLOAT;
		default:
			break;
		}
	}

	std::string ToVKShaderSourceCode(std::string_view src)
	{
		std::string result = src.data();

		int32_t outKeyIdx = 0;
		int32_t inKeyIdx = 0;
		int32_t uniformKeyIdx = 0;

		for (int32_t idx = 0; idx < result.size(); ++idx)
		{
			char c = result[idx];

			if (c == 'u')
			{
				std::string keyword = "uniform ";
				auto literal = result.substr(idx, keyword.size());
				if (literal == keyword)
				{
					std::string insertCode = "layout(set=0,binding=" + std::to_string((uniformKeyIdx++)) + ") ";
					result.insert(idx, insertCode, 0, insertCode.size());
					idx += insertCode.size() + keyword.size();

					std::string samplerkeyword = "sampler";
					literal = result.substr(idx, samplerkeyword.size());
					if (literal == samplerkeyword)
					{
						while (result[idx] != ';')
							++idx;
					}
					else
					{
						auto uniformDeclName = "set0binding" + std::to_string((uniformKeyIdx - 1)) + " {";
						result.insert(idx, uniformDeclName);
						while (result[idx] != ';')
							++idx;

						result.insert(idx + 1, "};");
					}
				}
			}
			else if (c == 'i')
			{
				std::string keyword = "in ";
				auto literal = result.substr(idx, keyword.size());
				if (literal == keyword)
				{
					std::string insertCode = "layout(location=" + std::to_string((inKeyIdx++)) + ") ";
					result.insert(idx, insertCode, 0, insertCode.size());

					idx += insertCode.size() + keyword.size();
				}
			}
			else if (c == 'o')
			{
				std::string keyword = "out ";
				auto literal = result.substr(idx, keyword.size());
				if (literal == keyword)
				{
					std::string insertCode = "layout(location=" + std::to_string((outKeyIdx++)) + ") ";
					result.insert(idx, insertCode, 0, insertCode.size());

					idx += insertCode.size() + keyword.size();
				}
			}
		}

		std::string header = "#version 450 core\n";

		std::string definition = "#define gl_VertexIndex gl_VertexID\n"
								 "#define gl_InstanceIndex gl_InstanceID\n";

		auto content = header + definition + result + "\n";

		return content;
	}
}