#pragma once
#include <cstdint>
#include "Defs.h"
#include "Color.h"
#include "Graphics/PrimitiveGeometry.h"
#include "Shader.h"
namespace mulberry
{
    class GraphicsPipeline : GRAPHICS_RHI_IMPL_DECL(GraphicsPipeline)
    {
    public:
        GraphicsPipeline();
        ~GraphicsPipeline();

        GraphicsPipeline &SetVertexShader(Shader *shader);
        GraphicsPipeline &SetTessellationControlShader(Shader *shader);
        GraphicsPipeline &SetTessellationEvaluationShader(Shader *shader);
        GraphicsPipeline &SetGeometryShader(Shader *shader);
        GraphicsPipeline &SetFragmentShader(Shader *shader);

        GraphicsPipeline &AddVertexInputBinding(uint32_t binding, uint32_t stride);
        // GraphicsPipeline &AddVertexInputAttribute(uint32_t binding, uint32_t location, uint32_t offset, Format format);

        GraphicsPipeline &SetPrimitiveTopology(PrimitiveTopology topology);
        GraphicsPipeline &SetPrimitiveRestartEnable(bool isOpen);

        GraphicsPipeline &SetCullMode(CullMode cullMode);
        GraphicsPipeline &SetPolygonMode(PolygonMode mode);
        GraphicsPipeline &SetFrontFace(FrontFace frontFace);
        GraphicsPipeline &SetLineWidth(float lw);

        GraphicsPipeline &SetRasterDiscardEnable(bool v);

        GraphicsPipeline &SetDepthBiasEnable(bool enable);
        GraphicsPipeline &SetDepthClampEnable(bool enable);

        GraphicsPipeline &SetDepthBiasClamp(float v);
        GraphicsPipeline &SetDepthBiasConstantFactor(float v);
        GraphicsPipeline &SetDepthBiasSlopeFactor(float v);

        GraphicsPipeline &SetSampleCount(SampleCount msaa);
        GraphicsPipeline &SetAlphaToCoverageEnable(bool enable);
        GraphicsPipeline &SetAlphaToOneEnable(bool enable);
        GraphicsPipeline &SetMinSampleShading(float v);
    };

    class ComputePipeline: GRAPHICS_RHI_IMPL_DECL(GraphicsPipeline)
    {
    public:
        ComputePipeline();
        ~ComputePipeline();
    };
}