#pragma once
#include <cstdint>
#include <string_view>

namespace GL
{
    uint32_t DataStrToGLDataType(std::string_view dataStr);
}
