#include "Utils.h"
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include "Logger.h"
#include "Graphics/RHI/VK/Image.h"

namespace mulberry::vk
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

		std::unique_ptr<glslang::TShader> shader = std::make_unique<glslang::TShader>(stage);

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

		program.addShader(shader.get());

		if (!program.link(messages))
		{
			std::cout << program.getInfoLog() << std::endl;
			std::cout << program.getInfoDebugLog() << std::endl;
			return {};
		}

		std::vector<uint32_t> result;

		glslang::GlslangToSpv(*program.getIntermediate(stage), result);

		glslang::FinalizeProcess();
		
		return result;
	}

	Format ToFormat(VkFormat format)
	{
#define CASE(x)           \
	case VK_FORMAT_##x:   \
		return Format::x; \
		break;

		switch (format)
		{
			CASE(UNDEFINED);
			CASE(R4G4_UNORM_PACK8);
			CASE(R4G4B4A4_UNORM_PACK16);
			CASE(B4G4R4A4_UNORM_PACK16);
			CASE(R5G6B5_UNORM_PACK16);
			CASE(B5G6R5_UNORM_PACK16);
			CASE(R5G5B5A1_UNORM_PACK16);
			CASE(B5G5R5A1_UNORM_PACK16);
			CASE(A1R5G5B5_UNORM_PACK16);
			CASE(R8_UNORM);
			CASE(R8_SNORM);
			CASE(R8_USCALED);
			CASE(R8_SSCALED);
			CASE(R8_UINT);
			CASE(R8_SINT);
			CASE(R8_SRGB);

			CASE(R8G8_UNORM);
			CASE(R8G8_SNORM);
			CASE(R8G8_USCALED);
			CASE(R8G8_SSCALED);
			CASE(R8G8_UINT);
			CASE(R8G8_SINT);
			CASE(R8G8_SRGB);

			CASE(R8G8B8_UNORM);
			CASE(R8G8B8_SNORM);
			CASE(R8G8B8_USCALED);
			CASE(R8G8B8_SSCALED);
			CASE(R8G8B8_UINT);
			CASE(R8G8B8_SINT);
			CASE(R8G8B8_SRGB);

			CASE(B8G8R8_UNORM);
			CASE(B8G8R8_SNORM);
			CASE(B8G8R8_USCALED);
			CASE(B8G8R8_SSCALED);
			CASE(B8G8R8_UINT);
			CASE(B8G8R8_SINT);
			CASE(B8G8R8_SRGB);

			CASE(R8G8B8A8_UNORM);
			CASE(R8G8B8A8_SNORM);
			CASE(R8G8B8A8_USCALED);
			CASE(R8G8B8A8_SSCALED);
			CASE(R8G8B8A8_UINT);
			CASE(R8G8B8A8_SINT);
			CASE(R8G8B8A8_SRGB);

			CASE(B8G8R8A8_UNORM);
			CASE(B8G8R8A8_SNORM);
			CASE(B8G8R8A8_USCALED);
			CASE(B8G8R8A8_SSCALED);
			CASE(B8G8R8A8_UINT);
			CASE(B8G8R8A8_SINT);
			CASE(B8G8R8A8_SRGB);

			CASE(A8B8G8R8_UNORM_PACK32);
			CASE(A8B8G8R8_SNORM_PACK32);
			CASE(A8B8G8R8_USCALED_PACK32);
			CASE(A8B8G8R8_SSCALED_PACK32);
			CASE(A8B8G8R8_UINT_PACK32);
			CASE(A8B8G8R8_SINT_PACK32);
			CASE(A8B8G8R8_SRGB_PACK32);

			CASE(A2R10G10B10_UNORM_PACK32);
			CASE(A2R10G10B10_SNORM_PACK32);
			CASE(A2R10G10B10_USCALED_PACK32);
			CASE(A2R10G10B10_SSCALED_PACK32);
			CASE(A2R10G10B10_UINT_PACK32);
			CASE(A2R10G10B10_SINT_PACK32);

			CASE(A2B10G10R10_UNORM_PACK32);
			CASE(A2B10G10R10_SNORM_PACK32);
			CASE(A2B10G10R10_USCALED_PACK32);
			CASE(A2B10G10R10_SSCALED_PACK32);
			CASE(A2B10G10R10_UINT_PACK32);
			CASE(A2B10G10R10_SINT_PACK32);

			CASE(R16_UNORM);
			CASE(R16_SNORM);
			CASE(R16_USCALED);
			CASE(R16_SSCALED);
			CASE(R16_UINT);
			CASE(R16_SINT);
			CASE(R16_SFLOAT);

			CASE(R16G16_UNORM);
			CASE(R16G16_SNORM);
			CASE(R16G16_USCALED);
			CASE(R16G16_SSCALED);
			CASE(R16G16_UINT);
			CASE(R16G16_SINT);
			CASE(R16G16_SFLOAT);

			CASE(R16G16B16_UNORM);
			CASE(R16G16B16_SNORM);
			CASE(R16G16B16_USCALED);
			CASE(R16G16B16_SSCALED);
			CASE(R16G16B16_UINT);
			CASE(R16G16B16_SINT);
			CASE(R16G16B16_SFLOAT);

			CASE(R16G16B16A16_UNORM);
			CASE(R16G16B16A16_SNORM);
			CASE(R16G16B16A16_USCALED);
			CASE(R16G16B16A16_SSCALED);
			CASE(R16G16B16A16_UINT);
			CASE(R16G16B16A16_SINT);
			CASE(R16G16B16A16_SFLOAT);

			CASE(R32_UINT);
			CASE(R32_SINT);
			CASE(R32_SFLOAT);

			CASE(R32G32_UINT);
			CASE(R32G32_SINT);
			CASE(R32G32_SFLOAT);

			CASE(R32G32B32_UINT);
			CASE(R32G32B32_SINT);
			CASE(R32G32B32_SFLOAT);

			CASE(R32G32B32A32_UINT);
			CASE(R32G32B32A32_SINT);
			CASE(R32G32B32A32_SFLOAT);

			CASE(R64_UINT);
			CASE(R64_SINT);
			CASE(R64_SFLOAT);

			CASE(R64G64_UINT);
			CASE(R64G64_SINT);
			CASE(R64G64_SFLOAT);

			CASE(R64G64B64_UINT);
			CASE(R64G64B64_SINT);
			CASE(R64G64B64_SFLOAT);

			CASE(R64G64B64A64_UINT);
			CASE(R64G64B64A64_SINT);
			CASE(R64G64B64A64_SFLOAT);

			CASE(B10G11R11_UFLOAT_PACK32);
			CASE(E5B9G9R9_UFLOAT_PACK32);

			CASE(D16_UNORM);
			CASE(X8_D24_UNORM_PACK32);
			CASE(D32_SFLOAT);
			CASE(S8_UINT);
			CASE(D16_UNORM_S8_UINT);
			CASE(D24_UNORM_S8_UINT);
			CASE(D32_SFLOAT_S8_UINT);
			CASE(BC1_RGB_UNORM_BLOCK);
			CASE(BC1_RGB_SRGB_BLOCK);
			CASE(BC1_RGBA_UNORM_BLOCK);
			CASE(BC1_RGBA_SRGB_BLOCK);
			CASE(BC2_UNORM_BLOCK);
			CASE(BC2_SRGB_BLOCK);
			CASE(BC3_UNORM_BLOCK);
			CASE(BC3_SRGB_BLOCK);
			CASE(BC4_UNORM_BLOCK);
			CASE(BC4_SNORM_BLOCK);
			CASE(BC5_UNORM_BLOCK);
			CASE(BC5_SNORM_BLOCK);

			CASE(BC6H_UFLOAT_BLOCK);
			CASE(BC6H_SFLOAT_BLOCK);
			CASE(BC7_UNORM_BLOCK);
			CASE(BC7_SRGB_BLOCK);
			CASE(ETC2_R8G8B8_UNORM_BLOCK);
			CASE(ETC2_R8G8B8_SRGB_BLOCK);
			CASE(ETC2_R8G8B8A1_UNORM_BLOCK);
			CASE(ETC2_R8G8B8A1_SRGB_BLOCK);
			CASE(ETC2_R8G8B8A8_UNORM_BLOCK);
			CASE(ETC2_R8G8B8A8_SRGB_BLOCK);
			CASE(EAC_R11_UNORM_BLOCK);
			CASE(EAC_R11_SNORM_BLOCK);
			CASE(EAC_R11G11_UNORM_BLOCK);
			CASE(EAC_R11G11_SNORM_BLOCK);
			CASE(ASTC_4x4_UNORM_BLOCK);
			CASE(ASTC_4x4_SRGB_BLOCK);
			CASE(ASTC_5x4_UNORM_BLOCK);
			CASE(ASTC_5x4_SRGB_BLOCK);
			CASE(ASTC_5x5_UNORM_BLOCK);
			CASE(ASTC_5x5_SRGB_BLOCK);
			CASE(ASTC_6x5_UNORM_BLOCK);
			CASE(ASTC_6x5_SRGB_BLOCK);
			CASE(ASTC_6x6_UNORM_BLOCK);
			CASE(ASTC_6x6_SRGB_BLOCK);
			CASE(ASTC_8x5_UNORM_BLOCK);
			CASE(ASTC_8x5_SRGB_BLOCK);
			CASE(ASTC_8x6_UNORM_BLOCK);
			CASE(ASTC_8x6_SRGB_BLOCK);
			CASE(ASTC_8x8_UNORM_BLOCK);
			CASE(ASTC_8x8_SRGB_BLOCK);
			CASE(ASTC_10x5_UNORM_BLOCK);
			CASE(ASTC_10x5_SRGB_BLOCK);
			CASE(ASTC_10x6_UNORM_BLOCK);
			CASE(ASTC_10x6_SRGB_BLOCK);
			CASE(ASTC_10x8_UNORM_BLOCK);
			CASE(ASTC_10x8_SRGB_BLOCK);
			CASE(ASTC_10x10_UNORM_BLOCK);
			CASE(ASTC_10x10_SRGB_BLOCK);
			CASE(ASTC_12x10_UNORM_BLOCK);
			CASE(ASTC_12x10_SRGB_BLOCK);
			CASE(ASTC_12x12_UNORM_BLOCK);
			CASE(ASTC_12x12_SRGB_BLOCK);
			CASE(G8B8G8R8_422_UNORM);
			CASE(B8G8R8G8_422_UNORM);
			CASE(G8_B8_R8_3PLANE_420_UNORM);
			CASE(G8_B8R8_2PLANE_420_UNORM);
			CASE(G8_B8_R8_3PLANE_422_UNORM);
			CASE(G8_B8R8_2PLANE_422_UNORM);
			CASE(G8_B8_R8_3PLANE_444_UNORM);
			CASE(R10X6_UNORM_PACK16);
			CASE(R10X6G10X6_UNORM_2PACK16);
			CASE(R10X6G10X6B10X6A10X6_UNORM_4PACK16);
			CASE(G10X6B10X6G10X6R10X6_422_UNORM_4PACK16);
			CASE(B10X6G10X6R10X6G10X6_422_UNORM_4PACK16);
			CASE(G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16);
			CASE(G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16);
			CASE(G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16);
			CASE(G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16);
			CASE(G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16);
			CASE(R12X4_UNORM_PACK16);
			CASE(R12X4G12X4_UNORM_2PACK16);
			CASE(R12X4G12X4B12X4A12X4_UNORM_4PACK16);
			CASE(G12X4B12X4G12X4R12X4_422_UNORM_4PACK16);
			CASE(B12X4G12X4R12X4G12X4_422_UNORM_4PACK16);
			CASE(G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16);
			CASE(G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16);
			CASE(G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16);
			CASE(G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16);
			CASE(G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16);
			CASE(G16B16G16R16_422_UNORM);
			CASE(B16G16R16G16_422_UNORM);
			CASE(G16_B16_R16_3PLANE_420_UNORM);
			CASE(G16_B16R16_2PLANE_420_UNORM);
			CASE(G16_B16_R16_3PLANE_422_UNORM);
			CASE(G16_B16R16_2PLANE_422_UNORM);
			CASE(G16_B16_R16_3PLANE_444_UNORM);
			CASE(G8_B8R8_2PLANE_444_UNORM);
			CASE(G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16);
			CASE(G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16);
			CASE(G16_B16R16_2PLANE_444_UNORM);
			CASE(A4R4G4B4_UNORM_PACK16);
			CASE(A4B4G4R4_UNORM_PACK16);
			CASE(ASTC_4x4_SFLOAT_BLOCK);
			CASE(ASTC_5x4_SFLOAT_BLOCK);
			CASE(ASTC_5x5_SFLOAT_BLOCK);
			CASE(ASTC_6x5_SFLOAT_BLOCK);
			CASE(ASTC_6x6_SFLOAT_BLOCK);
			CASE(ASTC_8x5_SFLOAT_BLOCK);
			CASE(ASTC_8x6_SFLOAT_BLOCK);
			CASE(ASTC_8x8_SFLOAT_BLOCK);
			CASE(ASTC_10x5_SFLOAT_BLOCK);
			CASE(ASTC_10x6_SFLOAT_BLOCK);
			CASE(ASTC_10x8_SFLOAT_BLOCK);
			CASE(ASTC_10x10_SFLOAT_BLOCK);
			CASE(ASTC_12x10_SFLOAT_BLOCK);
			CASE(ASTC_12x12_SFLOAT_BLOCK);
			CASE(PVRTC1_2BPP_UNORM_BLOCK_IMG);
			CASE(PVRTC1_4BPP_UNORM_BLOCK_IMG);
			CASE(PVRTC2_2BPP_UNORM_BLOCK_IMG);
			CASE(PVRTC2_4BPP_UNORM_BLOCK_IMG);
			CASE(PVRTC1_2BPP_SRGB_BLOCK_IMG);
			CASE(PVRTC1_4BPP_SRGB_BLOCK_IMG);
			CASE(PVRTC2_2BPP_SRGB_BLOCK_IMG);
			CASE(PVRTC2_4BPP_SRGB_BLOCK_IMG);
		default:
			return Format::UNDEFINED;
		}
#undef CASE
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

	VkSampleCountFlagBits ToVkSampleCount(mulberry::SampleCount count)
	{
		switch (count)
		{
		case mulberry::SampleCount::X1:
			return VK_SAMPLE_COUNT_1_BIT;
		case mulberry::SampleCount::X2:
			return VK_SAMPLE_COUNT_2_BIT;
		case mulberry::SampleCount::X4:
			return VK_SAMPLE_COUNT_4_BIT;
		case mulberry::SampleCount::X8:
			return VK_SAMPLE_COUNT_8_BIT;
		case mulberry::SampleCount::X16:
			return VK_SAMPLE_COUNT_16_BIT;
		case mulberry::SampleCount::X32:
			return VK_SAMPLE_COUNT_32_BIT;
		case mulberry::SampleCount::X64:
			return VK_SAMPLE_COUNT_64_BIT;
		default:
			return VK_SAMPLE_COUNT_1_BIT;
		}
	}

	VkFrontFace ToVkFrontFace(mulberry::FrontFace frontFace)
	{
		switch (frontFace)
		{
		case mulberry::FrontFace::CW:
			return VK_FRONT_FACE_CLOCKWISE;
		case mulberry::FrontFace::CCW:
			return VK_FRONT_FACE_COUNTER_CLOCKWISE;
		default:
			return VK_FRONT_FACE_CLOCKWISE;
		}
	}

	VkCullModeFlagBits ToVkCullMode(mulberry::CullMode cullMode)
	{
		switch (cullMode)
		{
		case mulberry::CullMode::NONE:
			return VK_CULL_MODE_NONE;
		case mulberry::CullMode::FRONT:
			return VK_CULL_MODE_FRONT_BIT;
		case mulberry::CullMode::BACK:
			return VK_CULL_MODE_BACK_BIT;
		case mulberry::CullMode::BOTH:
			return VK_CULL_MODE_FRONT_AND_BACK;
		default:
			return VK_CULL_MODE_NONE;
		}
	}

	VkFilter ToVkFilterMode(FilterMode filterMode)
	{
		switch (filterMode)
		{
		case mulberry::FilterMode::NEAREST:
			return VK_FILTER_NEAREST;
		case mulberry::FilterMode::LINEAR:
			return VK_FILTER_LINEAR;
		default:
			return VK_FILTER_NEAREST;
		}
	}

	VkSamplerAddressMode ToVkWrapMode(WrapMode wrapMode)
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

	VkSamplerMipmapMode ToVkMipMapMode(MipMapMode mipmapMode)
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

	VkBorderColor ToVkBorderColor(BorderColor borderColor)
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

	VkShaderStageFlagBits ToVkShaderStage(ShaderStage shaderStage)
	{
		VkShaderStageFlags result = 0;
		if ((shaderStage & ShaderStage::VERTEX) == ShaderStage::VERTEX)
			result |= VK_SHADER_STAGE_VERTEX_BIT;
		if ((shaderStage & ShaderStage::FRAGMENT) == ShaderStage::FRAGMENT)
			result |= VK_SHADER_STAGE_FRAGMENT_BIT;
		if ((shaderStage & ShaderStage::GEOMETRY) == ShaderStage::GEOMETRY)
			result |= VK_SHADER_STAGE_GEOMETRY_BIT;
		if ((shaderStage & ShaderStage::TESSELLATION_CONTROL) == ShaderStage::TESSELLATION_CONTROL)
			result |= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		if ((shaderStage & ShaderStage::TESSELLATION_EVALUATION) == ShaderStage::TESSELLATION_EVALUATION)
			result |= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		if ((shaderStage & ShaderStage::ALL_GRAPHICS) == ShaderStage::ALL_GRAPHICS)
			result |= VK_SHADER_STAGE_ALL_GRAPHICS;
		if ((shaderStage & ShaderStage::ALL) == ShaderStage::ALL)
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

	VkPrimitiveTopology ToVkPrimitiveTopology(PrimitiveTopology primTopo)
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

	VkPolygonMode ToVkPolygonMode(PolygonMode polyMode)
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

	VkFormat ToVkFormat(Format format)
	{
#define CASE(x)               \
	case Format::x:           \
		return VK_FORMAT_##x; \
		break;

		switch (format)
		{
			CASE(UNDEFINED);
			CASE(R4G4_UNORM_PACK8);
			CASE(R4G4B4A4_UNORM_PACK16);
			CASE(B4G4R4A4_UNORM_PACK16);
			CASE(R5G6B5_UNORM_PACK16);
			CASE(B5G6R5_UNORM_PACK16);
			CASE(R5G5B5A1_UNORM_PACK16);
			CASE(B5G5R5A1_UNORM_PACK16);
			CASE(A1R5G5B5_UNORM_PACK16);
			CASE(R8_UNORM);
			CASE(R8_SNORM);
			CASE(R8_USCALED);
			CASE(R8_SSCALED);
			CASE(R8_UINT);
			CASE(R8_SINT);
			CASE(R8_SRGB);

			CASE(R8G8_UNORM);
			CASE(R8G8_SNORM);
			CASE(R8G8_USCALED);
			CASE(R8G8_SSCALED);
			CASE(R8G8_UINT);
			CASE(R8G8_SINT);
			CASE(R8G8_SRGB);

			CASE(R8G8B8_UNORM);
			CASE(R8G8B8_SNORM);
			CASE(R8G8B8_USCALED);
			CASE(R8G8B8_SSCALED);
			CASE(R8G8B8_UINT);
			CASE(R8G8B8_SINT);
			CASE(R8G8B8_SRGB);

			CASE(B8G8R8_UNORM);
			CASE(B8G8R8_SNORM);
			CASE(B8G8R8_USCALED);
			CASE(B8G8R8_SSCALED);
			CASE(B8G8R8_UINT);
			CASE(B8G8R8_SINT);
			CASE(B8G8R8_SRGB);

			CASE(R8G8B8A8_UNORM);
			CASE(R8G8B8A8_SNORM);
			CASE(R8G8B8A8_USCALED);
			CASE(R8G8B8A8_SSCALED);
			CASE(R8G8B8A8_UINT);
			CASE(R8G8B8A8_SINT);
			CASE(R8G8B8A8_SRGB);

			CASE(B8G8R8A8_UNORM);
			CASE(B8G8R8A8_SNORM);
			CASE(B8G8R8A8_USCALED);
			CASE(B8G8R8A8_SSCALED);
			CASE(B8G8R8A8_UINT);
			CASE(B8G8R8A8_SINT);
			CASE(B8G8R8A8_SRGB);

			CASE(A8B8G8R8_UNORM_PACK32);
			CASE(A8B8G8R8_SNORM_PACK32);
			CASE(A8B8G8R8_USCALED_PACK32);
			CASE(A8B8G8R8_SSCALED_PACK32);
			CASE(A8B8G8R8_UINT_PACK32);
			CASE(A8B8G8R8_SINT_PACK32);
			CASE(A8B8G8R8_SRGB_PACK32);

			CASE(A2R10G10B10_UNORM_PACK32);
			CASE(A2R10G10B10_SNORM_PACK32);
			CASE(A2R10G10B10_USCALED_PACK32);
			CASE(A2R10G10B10_SSCALED_PACK32);
			CASE(A2R10G10B10_UINT_PACK32);
			CASE(A2R10G10B10_SINT_PACK32);

			CASE(A2B10G10R10_UNORM_PACK32);
			CASE(A2B10G10R10_SNORM_PACK32);
			CASE(A2B10G10R10_USCALED_PACK32);
			CASE(A2B10G10R10_SSCALED_PACK32);
			CASE(A2B10G10R10_UINT_PACK32);
			CASE(A2B10G10R10_SINT_PACK32);

			CASE(R16_UNORM);
			CASE(R16_SNORM);
			CASE(R16_USCALED);
			CASE(R16_SSCALED);
			CASE(R16_UINT);
			CASE(R16_SINT);
			CASE(R16_SFLOAT);

			CASE(R16G16_UNORM);
			CASE(R16G16_SNORM);
			CASE(R16G16_USCALED);
			CASE(R16G16_SSCALED);
			CASE(R16G16_UINT);
			CASE(R16G16_SINT);
			CASE(R16G16_SFLOAT);

			CASE(R16G16B16_UNORM);
			CASE(R16G16B16_SNORM);
			CASE(R16G16B16_USCALED);
			CASE(R16G16B16_SSCALED);
			CASE(R16G16B16_UINT);
			CASE(R16G16B16_SINT);
			CASE(R16G16B16_SFLOAT);

			CASE(R16G16B16A16_UNORM);
			CASE(R16G16B16A16_SNORM);
			CASE(R16G16B16A16_USCALED);
			CASE(R16G16B16A16_SSCALED);
			CASE(R16G16B16A16_UINT);
			CASE(R16G16B16A16_SINT);
			CASE(R16G16B16A16_SFLOAT);

			CASE(R32_UINT);
			CASE(R32_SINT);
			CASE(R32_SFLOAT);

			CASE(R32G32_UINT);
			CASE(R32G32_SINT);
			CASE(R32G32_SFLOAT);

			CASE(R32G32B32_UINT);
			CASE(R32G32B32_SINT);
			CASE(R32G32B32_SFLOAT);

			CASE(R32G32B32A32_UINT);
			CASE(R32G32B32A32_SINT);
			CASE(R32G32B32A32_SFLOAT);

			CASE(R64_UINT);
			CASE(R64_SINT);
			CASE(R64_SFLOAT);

			CASE(R64G64_UINT);
			CASE(R64G64_SINT);
			CASE(R64G64_SFLOAT);

			CASE(R64G64B64_UINT);
			CASE(R64G64B64_SINT);
			CASE(R64G64B64_SFLOAT);

			CASE(R64G64B64A64_UINT);
			CASE(R64G64B64A64_SINT);
			CASE(R64G64B64A64_SFLOAT);

			CASE(B10G11R11_UFLOAT_PACK32);
			CASE(E5B9G9R9_UFLOAT_PACK32);

			CASE(D16_UNORM);
			CASE(X8_D24_UNORM_PACK32);
			CASE(D32_SFLOAT);
			CASE(S8_UINT);
			CASE(D16_UNORM_S8_UINT);
			CASE(D24_UNORM_S8_UINT);
			CASE(D32_SFLOAT_S8_UINT);
			CASE(BC1_RGB_UNORM_BLOCK);
			CASE(BC1_RGB_SRGB_BLOCK);
			CASE(BC1_RGBA_UNORM_BLOCK);
			CASE(BC1_RGBA_SRGB_BLOCK);
			CASE(BC2_UNORM_BLOCK);
			CASE(BC2_SRGB_BLOCK);
			CASE(BC3_UNORM_BLOCK);
			CASE(BC3_SRGB_BLOCK);
			CASE(BC4_UNORM_BLOCK);
			CASE(BC4_SNORM_BLOCK);
			CASE(BC5_UNORM_BLOCK);
			CASE(BC5_SNORM_BLOCK);

			CASE(BC6H_UFLOAT_BLOCK);
			CASE(BC6H_SFLOAT_BLOCK);
			CASE(BC7_UNORM_BLOCK);
			CASE(BC7_SRGB_BLOCK);
			CASE(ETC2_R8G8B8_UNORM_BLOCK);
			CASE(ETC2_R8G8B8_SRGB_BLOCK);
			CASE(ETC2_R8G8B8A1_UNORM_BLOCK);
			CASE(ETC2_R8G8B8A1_SRGB_BLOCK);
			CASE(ETC2_R8G8B8A8_UNORM_BLOCK);
			CASE(ETC2_R8G8B8A8_SRGB_BLOCK);
			CASE(EAC_R11_UNORM_BLOCK);
			CASE(EAC_R11_SNORM_BLOCK);
			CASE(EAC_R11G11_UNORM_BLOCK);
			CASE(EAC_R11G11_SNORM_BLOCK);
			CASE(ASTC_4x4_UNORM_BLOCK);
			CASE(ASTC_4x4_SRGB_BLOCK);
			CASE(ASTC_5x4_UNORM_BLOCK);
			CASE(ASTC_5x4_SRGB_BLOCK);
			CASE(ASTC_5x5_UNORM_BLOCK);
			CASE(ASTC_5x5_SRGB_BLOCK);
			CASE(ASTC_6x5_UNORM_BLOCK);
			CASE(ASTC_6x5_SRGB_BLOCK);
			CASE(ASTC_6x6_UNORM_BLOCK);
			CASE(ASTC_6x6_SRGB_BLOCK);
			CASE(ASTC_8x5_UNORM_BLOCK);
			CASE(ASTC_8x5_SRGB_BLOCK);
			CASE(ASTC_8x6_UNORM_BLOCK);
			CASE(ASTC_8x6_SRGB_BLOCK);
			CASE(ASTC_8x8_UNORM_BLOCK);
			CASE(ASTC_8x8_SRGB_BLOCK);
			CASE(ASTC_10x5_UNORM_BLOCK);
			CASE(ASTC_10x5_SRGB_BLOCK);
			CASE(ASTC_10x6_UNORM_BLOCK);
			CASE(ASTC_10x6_SRGB_BLOCK);
			CASE(ASTC_10x8_UNORM_BLOCK);
			CASE(ASTC_10x8_SRGB_BLOCK);
			CASE(ASTC_10x10_UNORM_BLOCK);
			CASE(ASTC_10x10_SRGB_BLOCK);
			CASE(ASTC_12x10_UNORM_BLOCK);
			CASE(ASTC_12x10_SRGB_BLOCK);
			CASE(ASTC_12x12_UNORM_BLOCK);
			CASE(ASTC_12x12_SRGB_BLOCK);
			CASE(G8B8G8R8_422_UNORM);
			CASE(B8G8R8G8_422_UNORM);
			CASE(G8_B8_R8_3PLANE_420_UNORM);
			CASE(G8_B8R8_2PLANE_420_UNORM);
			CASE(G8_B8_R8_3PLANE_422_UNORM);
			CASE(G8_B8R8_2PLANE_422_UNORM);
			CASE(G8_B8_R8_3PLANE_444_UNORM);
			CASE(R10X6_UNORM_PACK16);
			CASE(R10X6G10X6_UNORM_2PACK16);
			CASE(R10X6G10X6B10X6A10X6_UNORM_4PACK16);
			CASE(G10X6B10X6G10X6R10X6_422_UNORM_4PACK16);
			CASE(B10X6G10X6R10X6G10X6_422_UNORM_4PACK16);
			CASE(G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16);
			CASE(G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16);
			CASE(G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16);
			CASE(G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16);
			CASE(G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16);
			CASE(R12X4_UNORM_PACK16);
			CASE(R12X4G12X4_UNORM_2PACK16);
			CASE(R12X4G12X4B12X4A12X4_UNORM_4PACK16);
			CASE(G12X4B12X4G12X4R12X4_422_UNORM_4PACK16);
			CASE(B12X4G12X4R12X4G12X4_422_UNORM_4PACK16);
			CASE(G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16);
			CASE(G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16);
			CASE(G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16);
			CASE(G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16);
			CASE(G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16);
			CASE(G16B16G16R16_422_UNORM);
			CASE(B16G16R16G16_422_UNORM);
			CASE(G16_B16_R16_3PLANE_420_UNORM);
			CASE(G16_B16R16_2PLANE_420_UNORM);
			CASE(G16_B16_R16_3PLANE_422_UNORM);
			CASE(G16_B16R16_2PLANE_422_UNORM);
			CASE(G16_B16_R16_3PLANE_444_UNORM);
			CASE(G8_B8R8_2PLANE_444_UNORM);
			CASE(G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16);
			CASE(G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16);
			CASE(G16_B16R16_2PLANE_444_UNORM);
			CASE(A4R4G4B4_UNORM_PACK16);
			CASE(A4B4G4R4_UNORM_PACK16);
			CASE(ASTC_4x4_SFLOAT_BLOCK);
			CASE(ASTC_5x4_SFLOAT_BLOCK);
			CASE(ASTC_5x5_SFLOAT_BLOCK);
			CASE(ASTC_6x5_SFLOAT_BLOCK);
			CASE(ASTC_6x6_SFLOAT_BLOCK);
			CASE(ASTC_8x5_SFLOAT_BLOCK);
			CASE(ASTC_8x6_SFLOAT_BLOCK);
			CASE(ASTC_8x8_SFLOAT_BLOCK);
			CASE(ASTC_10x5_SFLOAT_BLOCK);
			CASE(ASTC_10x6_SFLOAT_BLOCK);
			CASE(ASTC_10x8_SFLOAT_BLOCK);
			CASE(ASTC_10x10_SFLOAT_BLOCK);
			CASE(ASTC_12x10_SFLOAT_BLOCK);
			CASE(ASTC_12x12_SFLOAT_BLOCK);
			CASE(PVRTC1_2BPP_UNORM_BLOCK_IMG);
			CASE(PVRTC1_4BPP_UNORM_BLOCK_IMG);
			CASE(PVRTC2_2BPP_UNORM_BLOCK_IMG);
			CASE(PVRTC2_4BPP_UNORM_BLOCK_IMG);
			CASE(PVRTC1_2BPP_SRGB_BLOCK_IMG);
			CASE(PVRTC1_4BPP_SRGB_BLOCK_IMG);
			CASE(PVRTC2_2BPP_SRGB_BLOCK_IMG);
			CASE(PVRTC2_4BPP_SRGB_BLOCK_IMG);
		default:
			return VK_FORMAT_UNDEFINED;
		}
#undef CASE
	}

	VkAttachmentLoadOp ToLoadOp(AttachmentLoad op)
	{
		switch (op)
		{
		case AttachmentLoad::LOAD:
			return VK_ATTACHMENT_LOAD_OP_LOAD;
		case AttachmentLoad::CLEAR:
			return VK_ATTACHMENT_LOAD_OP_CLEAR;
		default:
			return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		}
	}

	VkAttachmentStoreOp ToStoreOp(AttachmentStore op)
	{
		switch (op)
		{
		case AttachmentStore::STORE:
			return VK_ATTACHMENT_STORE_OP_STORE;
		default:
			return VK_ATTACHMENT_STORE_OP_DONT_CARE;
		}
	}

	VkAttachmentDescription ToVkAttachmentDescription(const ColorAttachment &colorAttachment)
	{
		VkAttachmentDescription result{};
		result.flags = 0;
		result.format = ToVkFormat(colorAttachment.texture->GetVkImpl()->GetImage()->GetFormat());
		result.samples = VK_SAMPLE_COUNT_1_BIT;
		result.loadOp = ToLoadOp(colorAttachment.loadOp);
		result.storeOp = ToStoreOp(colorAttachment.storeOp);
		result.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		result.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		result.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		result.finalLayout = VkImageLayout(VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL | VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

		return result;
	}
}