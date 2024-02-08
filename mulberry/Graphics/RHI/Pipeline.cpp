#include "Pipeline.h"
#include "App.h"
#include "VK/Pipeline.h"
namespace mulberry::rhi
{
    RasterPipeline::RasterPipeline()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKRasterPipelineImpl = std::make_unique<vk::RasterPipeline>());
    }

    RasterPipeline::~RasterPipeline()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKRasterPipelineImpl.reset(nullptr));
    }

    ComputePipeline::ComputePipeline()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKComputePipelineImpl = std::make_unique<vk::ComputePipeline>());
    }
    
    ComputePipeline::~ComputePipeline()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKComputePipelineImpl.reset(nullptr));
    }
}