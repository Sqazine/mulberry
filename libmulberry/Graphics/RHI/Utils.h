#pragma once
#include "Core/Logger.h"

#define NOT_IMPLEMENTATE()                        \
    do                                            \
    {                                             \
        MULBERRY_CORE_ERROR("Not implement yet"); \
    } while (false);

#define GRAPHICS_RHI_IMPL_SWITCHER(vkImpl)     \
    switch (AppConfig::graphicsConfig.backend) \
    {                                          \
    case GraphicsBackend::VK:                  \
        vkImpl;                                \
        break;                                 \
    default:                                   \
        NOT_IMPLEMENTATE();                    \
        break;                                 \
    }