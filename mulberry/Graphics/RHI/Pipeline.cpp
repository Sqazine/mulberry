#include "Pipeline.h"
#include "App.h"
#include "Graphics/RHI/VK/Pipeline.h"
namespace mulberry::rhi
{
    GraphicsPipeline::GraphicsPipeline()
    {
    }

    GraphicsPipeline::~GraphicsPipeline()
    {
    }

    GraphicsPipeline &GraphicsPipeline::SetVertexShader(Shader *shader)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetVertexShader(shader->GetVkImpl()));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetTessellationControlShader(Shader *shader)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetTessellationControlShader(shader->GetVkImpl()));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetTessellationEvaluationShader(Shader *shader)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetTessellationEvaluationShader(shader->GetVkImpl()));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetGeometryShader(Shader *shader)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetGeometryShader(shader->GetVkImpl()));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetFragmentShader(Shader *shader)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetFragmentShader(shader->GetVkImpl()));
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetPrimitiveTopology(PrimitiveTopology topology)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetPrimitiveTopology(topology));
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetPrimitiveRestartEnable(bool isOpen)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetPrimitiveRestartEnable(isOpen));
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetCullMode(CullMode cullMode)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetCullMode(cullMode));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetPolygonMode(PolygonMode mode)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetPolygonMode(mode));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetFrontFace(FrontFace frontFace)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetFrontFace(frontFace));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetLineWidth(float lw)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetLineWidth(lw));
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetRasterDiscardEnable(bool v)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetRasterDiscardEnable(v));
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetDepthBiasEnable(bool enable)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetDepthBiasEnable(enable));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetDepthClampEnable(bool enable)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetDepthClampEnable(enable));
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetDepthBiasClamp(float v)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetDepthBiasClamp(v));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetDepthBiasConstantFactor(float v)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetDepthBiasConstantFactor(v));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetDepthBiasSlopeFactor(float v)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetDepthBiasSlopeFactor(v));
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetSampleCount(SampleCount msaa)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetSampleCount(msaa));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetAlphaToCoverageEnable(bool enable)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetAlphaToCoverageEnable(enable));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetAlphaToOneEnable(bool enable)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetAlphaToOneEnable(enable));
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetMinSampleShading(float v)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetMinSampleShading(v));
        return *this;
    }

    ComputePipeline::ComputePipeline()
    {
    }

    ComputePipeline::~ComputePipeline()
    {
    }
}