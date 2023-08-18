#pragma once
#include <cstdint>
namespace mulberry
{
     enum class ShaderType;
     enum class PrimitiveRenderType;

     uint32_t ToGLShaderType(ShaderType type);
     uint32_t ToGLPrimitiveType(PrimitiveRenderType type);
}