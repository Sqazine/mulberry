#pragma once
#include "RHI/Enum.h"
namespace mulberry
{
    enum class GraphicsBackend
    {
        GL,
        VK,
    };

    struct GraphicsConfig
    {
        GraphicsBackend backend = GraphicsBackend::VK;
        bool useVSync = false;
        float frameRate = 0;
        bool useDoubleBuffer = false;
        rhi::SampleCount msaaSample = rhi::SampleCount::X2;
    };
}