#pragma once
#include <unordered_map>

namespace Pe2
{

    class AssetManager
    {
    public:
        AssetManager();
        ~AssetManager();

        const class ImgData& LoadImgData(const std::string &filePath);
        const std::string& LoadText(std::string_view path);
    private:
        std::unordered_map<std::string, class ImgData> mImgDatas;
        std::unordered_map<std::string, std::string> mTexts;
    };
}