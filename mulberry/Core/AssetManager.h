#pragma once
#include <unordered_map>
#include <string>

namespace mulberry
{
    struct ImageData
    {
        std::vector<uint8_t> pixels{};
        uint32_t width = 0, height = 0, channel = 4;
    };

    class AssetManager
    {
    public:
        AssetManager();
        ~AssetManager();

        const ImageData &LoadImageData(const std::string &filePath);
        const std::string &LoadText(std::string_view path);

    private:
        std::unordered_map<std::string, ImageData> mImageDatas;
        std::unordered_map<std::string, std::string> mTexts;
    };
}