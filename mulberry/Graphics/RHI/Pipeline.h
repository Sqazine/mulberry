#pragma once
#include <cstdint>
#include "Color.h"
#include "Graphics/PrimitiveGeometry.h"
#include "Graphics/RHI/VK/Pipeline.h"
namespace mulberry::rhi
{
    class RasterPipeline
    {
    public:
        RasterPipeline();
        ~RasterPipeline();
    private:
        std::unique_ptr<vk::RasterPipeline> mVKRasterPipelineImpl;
    };

      class ComputePipeline
    {
    public:
        ComputePipeline();
        ~ComputePipeline();
    private:
        std::unique_ptr<vk::ComputePipeline> mVKComputePipelineImpl;
    };
}