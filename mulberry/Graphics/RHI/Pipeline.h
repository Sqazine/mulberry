#pragma once
#include <cstdint>
#include "Math/Color.h"
#include "Graphics/PrimitiveGeometry.h"
#include "Graphics/RHI/VK/Pipeline.h"
namespace mulberry
{
    class RasterPipeline
    {
    public:
        RasterPipeline();
        ~RasterPipeline();
    private:
        std::unique_ptr<vk::RasterPipeline> mVKRasterPipelineImpl;
    };
}