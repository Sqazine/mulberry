#pragma once
#include "Enum.h"
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
        bool useDoubleBuffer = true;
        SampleCount msaaSample = SampleCount::X2;
    };
}