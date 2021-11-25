#pragma once
#include <cstdint>
#include <vector>
#include <string_view>

struct ImgData
{
    std::vector<uint8_t> pixels;
    uint32_t width, height, channels;

    ImgData() : width(0), height(0), channels(0) {}
};

namespace Loader
{
    std::string LoadText(std::string_view path);
    ImgData LoadImgDataFromFile(std::string_view path, bool isFlip = false);
}