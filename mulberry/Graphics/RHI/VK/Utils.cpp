#include "Utils.h"
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include "Logger.h"

namespace mulberry::rhi::vk
{
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

	std::string ToShaderSourceCode(std::string_view src)
	{
		std::string result = src.data();

		int32_t outKeyIdx = 0;
		int32_t inKeyIdx = 0;
		int32_t uniformKeyIdx = 0;

		for (size_t idx = 0; idx < result.size(); ++idx)
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

	VkSampleCountFlagBits ToVkSampleCount(mulberry::rhi::SampleCount count)
	{
		switch (count)
		{
		case mulberry::rhi::SampleCount::X1:
			return VK_SAMPLE_COUNT_1_BIT;
		case mulberry::rhi::SampleCount::X2:
			return VK_SAMPLE_COUNT_2_BIT;
		case mulberry::rhi::SampleCount::X4:
			return VK_SAMPLE_COUNT_4_BIT;
		case mulberry::rhi::SampleCount::X8:
			return VK_SAMPLE_COUNT_8_BIT;
		case mulberry::rhi::SampleCount::X16:
			return VK_SAMPLE_COUNT_16_BIT;
		case mulberry::rhi::SampleCount::X32:
			return VK_SAMPLE_COUNT_32_BIT;
		case mulberry::rhi::SampleCount::X64:
			return VK_SAMPLE_COUNT_64_BIT;
		default:
			return VK_SAMPLE_COUNT_1_BIT;
		}
	}

	VkFrontFace ToVkFrontFace(mulberry::rhi::FrontFace frontFace)
	{
		switch (frontFace)
		{
		case mulberry::rhi::FrontFace::CW:
			return VK_FRONT_FACE_CLOCKWISE;
		case mulberry::rhi::FrontFace::CCW:
			return VK_FRONT_FACE_COUNTER_CLOCKWISE;
		default:
			return VK_FRONT_FACE_CLOCKWISE;
		}
	}

	VkCullModeFlagBits ToVkCullMode(mulberry::rhi::CullMode cullMode)
	{
		switch (cullMode)
		{
		case mulberry::rhi::CullMode::NONE:
			return VK_CULL_MODE_NONE;
		case mulberry::rhi::CullMode::FRONT:
			return VK_CULL_MODE_FRONT_BIT;
		case mulberry::rhi::CullMode::BACK:
			return VK_CULL_MODE_BACK_BIT;
		case mulberry::rhi::CullMode::BOTH:
			return VK_CULL_MODE_FRONT_AND_BACK;
		default:
			return VK_CULL_MODE_NONE;
		}
	}

	VkFilter ToVkFilterMode(rhi::FilterMode filterMode)
	{
		switch (filterMode)
		{
		case mulberry::rhi::FilterMode::NEAREST:
			return VK_FILTER_NEAREST;
		case mulberry::rhi::FilterMode::LINEAR:
			return VK_FILTER_LINEAR;
		default:
			return VK_FILTER_NEAREST;
		}
	}

	VkSamplerAddressMode ToVkWrapMode(rhi::WrapMode wrapMode)
	{
		switch (wrapMode)
		{
		case WrapMode::REPEAT:
			return VK_SAMPLER_ADDRESS_MODE_REPEAT;
		case WrapMode::MIRRORED_REPEAT:
			return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		case WrapMode::CLAMP_TO_EDGE:
			return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		case WrapMode::CLAMP_TO_BORDER:
			return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
		default:
			return VK_SAMPLER_ADDRESS_MODE_REPEAT;
		}
	}

	VkSamplerMipmapMode ToVkMipMapMode(rhi::MipMapMode mipmapMode)
	{
		switch (mipmapMode)
		{
		case MipMapMode::NEAREST:
			return VK_SAMPLER_MIPMAP_MODE_NEAREST;
		case MipMapMode::LINEAR:
			return VK_SAMPLER_MIPMAP_MODE_LINEAR;
		default:
			return VK_SAMPLER_MIPMAP_MODE_NEAREST;
		}
	}

	VkBorderColor ToVkBorderColor(rhi::BorderColor borderColor)
	{
		switch (borderColor)
		{
		case BorderColor::FLOAT_TRANSPARENT_BLACK:
			return VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
		case BorderColor::INT_TRANSPARENT_BLACK:
			return VK_BORDER_COLOR_INT_TRANSPARENT_BLACK;
		case BorderColor::FLOAT_OPAQUE_BLACK:
			return VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
		case BorderColor::INT_OPAQUE_BLACK:
			return VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		case BorderColor::FLOAT_OPAQUE_WHITE:
			return VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
		case BorderColor::INT_OPAQUE_WHITE:
			return VK_BORDER_COLOR_INT_OPAQUE_WHITE;
		default:
			return VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
		}
	}

	VkShaderStageFlagBits ToVkShaderStage(rhi::ShaderStage shaderStage)
	{
		VkShaderStageFlags result = 0;
		if ((shaderStage & rhi::ShaderStage::VERTEX) == ShaderStage::VERTEX)
			result |= VK_SHADER_STAGE_VERTEX_BIT;
		if ((shaderStage & rhi::ShaderStage::FRAGMENT) == ShaderStage::FRAGMENT)
			result |= VK_SHADER_STAGE_FRAGMENT_BIT;
		if ((shaderStage & rhi::ShaderStage::GEOMETRY) == ShaderStage::GEOMETRY)
			result |= VK_SHADER_STAGE_GEOMETRY_BIT;
		if ((shaderStage & rhi::ShaderStage::TESSELLATION_CONTROL) == ShaderStage::TESSELLATION_CONTROL)
			result |= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		if ((shaderStage & rhi::ShaderStage::TESSELLATION_EVALUATION) == ShaderStage::TESSELLATION_EVALUATION)
			result |= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		if ((shaderStage & rhi::ShaderStage::ALL_GRAPHICS) == ShaderStage::ALL_GRAPHICS)
			result |= VK_SHADER_STAGE_ALL_GRAPHICS;
		if ((shaderStage & rhi::ShaderStage::ALL) == ShaderStage::ALL)
			result |= VK_SHADER_STAGE_ALL;
		return (VkShaderStageFlagBits)result;
	}

	std::pair<VkViewport, VkRect2D> ToVkViewPort(const mulberry::Viewport &viewport)
	{
		VkViewport vkViewport;
		vkViewport.x = viewport.x;
		vkViewport.y = viewport.y;
		vkViewport.width = viewport.width;
		vkViewport.height = viewport.height;
		vkViewport.minDepth = 0.0f;
		vkViewport.maxDepth = 1.0f;

		VkRect2D vkScissor;
		vkScissor.extent.width = static_cast<uint32_t>(viewport.scissor.extent.x);
		vkScissor.extent.height = static_cast<uint32_t>(viewport.scissor.extent.y);
		vkScissor.offset.x = static_cast<int32_t>(viewport.scissor.offset.x);
		vkScissor.offset.y = static_cast<int32_t>(viewport.scissor.offset.y);
		return {vkViewport, vkScissor};
	}

	VkPrimitiveTopology ToVkPrimitiveTopology(rhi::PrimitiveTopology primTopo)
	{
		switch (primTopo)
		{
		case PrimitiveTopology::POINT_LIST:
			return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		case PrimitiveTopology::LINE_LIST:
			return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		case PrimitiveTopology::LINE_STRIP:
			return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
		case PrimitiveTopology::TRIANGLE_LIST:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		case PrimitiveTopology::TRIANGLE_STRIP:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		case PrimitiveTopology::TRIANGLE_FAN:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
		case PrimitiveTopology::LINE_LIST_WITH_ADJACENCY:
			return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
		case PrimitiveTopology::LINE_STRIP_WITH_ADJACENCY:
			return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
		case PrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		case PrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
		default:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		}
	}

	VkPolygonMode ToVkPolygonMode(rhi::PolygonMode polyMode)
	{
		switch (polyMode)
		{
		case PolygonMode::FILL:
			return VK_POLYGON_MODE_FILL;
		case PolygonMode::LINE:
			return VK_POLYGON_MODE_LINE;
		case PolygonMode::POINT:
			return VK_POLYGON_MODE_POINT;
		default:
			return VK_POLYGON_MODE_FILL;
		}
	}

}