#include "Pipeline.h"
#include "App.h"
#include "VK/Pipeline.h"
namespace mulberry
{
    RasterPipeline::RasterPipeline()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKRasterPipelineImpl=std::make_unique<vk::RasterPipeline>())
    }

    RasterPipeline::~RasterPipeline()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKRasterPipelineImpl.reset(nullptr))
    }
}