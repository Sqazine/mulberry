

#include "AssetManager.h"
#include "Graphics/RHI/Texture.h"
#include <stb/stb_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Logger.h"
#include "Platform/IO.h"
namespace mulberry
{
    AssetManager::AssetManager()
    {
    }

    AssetManager::~AssetManager()
    {
    }

    const ImgData &AssetManager::LoadImgData(const std::string &filePath)
    {
        auto iter = mImgDatas.find(filePath);
        if (iter != mImgDatas.end())
            return iter->second;
        ImgData tmp;
        stbi_set_flip_vertically_on_load(true);
        uint8_t *data = stbi_load(filePath.c_str(), (int32_t *)&tmp.width, (int32_t *)&tmp.height, (int32_t*)&tmp.channel, STBI_default);
        tmp.pixels = std::vector<uint8_t>(data, data + (tmp.width * tmp.height * 4));
        mImgDatas[filePath] = tmp;
        return mImgDatas[filePath];
    }

    const std::string &AssetManager::LoadText(std::string_view path)
    {
        auto iter = mTexts.find(path.data());
        if (iter != mTexts.end())
            return iter->second;

        std::ifstream file(path.data(), std::ios::binary);
        if (!file.is_open())
        {
            MULBERRY_CORE_ERROR("failed to load text:{}\n");
            exit(1);
        }
        std::stringstream sstream;
        sstream << file.rdbuf();
        std::string content = sstream.str();
        file.close();

        mTexts[path.data()] = IO::LoadText(path);

        return mTexts[path.data()];
    }

}