#pragma once
#include <cstdint>
#include <string_view>

namespace Pe2::GL
{
    uint32_t DataStrToGLDataType(std::string_view dataStr);
}
