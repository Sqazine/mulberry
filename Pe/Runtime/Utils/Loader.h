#pragma once
#include <cstdint>
#include <vector>
#include <string_view>
#include "../Graphics/Texture.h"

namespace Pe2::Loader
{
    std::string LoadText(std::string_view path);
    ImgData LoadImgDataFromFile(std::string_view path, bool isFlip = false);
}