#pragma once
#include <unordered_map>
#include <string>


namespace mulberry
{
	struct ImgData
	{
		std::vector<uint8_t> pixels{};
		uint32_t width = 0, height = 0, channel = 4;
	};

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