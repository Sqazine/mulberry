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

#define SET(member, value) \
    if (member == value)   \
        return *this;      \
    member = value;        \
    mIsDirty = true;       \
    return *this;

#define SET_UNIQUE_PTR(member, value)               \
    if (member != nullptr && member.get() == value) \
        return *this;                               \
    member.reset(std::move(value));                 \
    mIsDirty = true;                                \
    return *this;