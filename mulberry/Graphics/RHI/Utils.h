#pragma once
#include "Core/Logger.h"
#ifdef _DEBUG
#define NOT_IMPLEMENTATE()                        \
    do                                            \
    {                                             \
        MULBERRY_CORE_ERROR("Not implement yet"); \
        assert(1);                                \
    } while (false);
#else
#define NOT_IMPLEMENTATE()                        \
    do                                            \
    {                                             \
        MULBERRY_CORE_ERROR("Not implement yet"); \
        exit(1);                                  \
    } while (false);
#endif

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