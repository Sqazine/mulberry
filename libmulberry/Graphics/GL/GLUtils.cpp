#include "GLUtils.h"
#include "Graphics/Shader.h"
#include "Graphics/RasterPipeline.h"
#include <unordered_map>
namespace mulberry
{
    uint32_t ToGLShaderType(ShaderType type)
    {
        const std::unordered_map<ShaderType, uint32_t> maps = {
            {ShaderType::VERTEX, GL_VERTEX_SHADER},
            {ShaderType::FRAGMENT, GL_FRAGMENT_SHADER},
            {ShaderType::GEOMETRY, GL_GEOMETRY_SHADER},
            {ShaderType::TESSELLATION_CONTROL, GL_TESS_CONTROL_SHADER},
            {ShaderType::TESSELLATION_EVAL, GL_TESS_EVALUATION_SHADER},
            {ShaderType::COMPUTE, GL_COMPUTE_SHADER},
        };

        return maps.find(type)->second;
    }


     uint32_t ToGLPrimitiveType(PrimitiveRenderType type)
    {
        const std::unordered_map<PrimitiveRenderType, uint32_t> maps = {
            {PrimitiveRenderType::POINT_LIST, GL_POINTS},
            {PrimitiveRenderType::LINE_LIST, GL_LINES},
            {PrimitiveRenderType::LINE_STRIP, GL_LINE_STRIP},
            {PrimitiveRenderType::TRIANGLE_LIST, GL_TRIANGLES},
            {PrimitiveRenderType::TRIANGLE_STRIP, GL_TRIANGLE_STRIP},
            {PrimitiveRenderType::TRIANGLE_FAN, GL_TRIANGLE_FAN},
        };

        return maps.find(type)->second;
    }
}