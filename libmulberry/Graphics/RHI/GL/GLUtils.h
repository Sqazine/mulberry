#pragma once
#include <cstdint>
#include "Graphics/RHI/RasterPipeline.h"
#include "Graphics/RHI/RasterPipelineState.h"
namespace mulberry
{
     enum class ShaderType;
     enum class PrimitiveRenderType;
     enum class WrapMode;
     enum class FilterMode;
     enum class Format;

     uint32_t ToGLShaderType(ShaderType type);
     uint32_t ToGLPrimitiveRenderType(PrimitiveRenderType type);

     uint32_t ToGLWarpMode(WrapMode mode);
     uint32_t ToGLFilterMode(FilterMode mode);
     uint32_t ToGLFormat(Format mode);

     uint32_t ToGLBlendFunc(BlendFunc mode);

     std::string ToGLShaderSourceCode(std::string_view source);

     void ToGLRawPSO(const RasterPipelineState& state);
     void ToDefaultGLRawPSO();
}