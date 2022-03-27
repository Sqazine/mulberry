

#include "AssetManager.h"
#include "Graphics/GL/Texture.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
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
        uint8_t *data = stbi_load(filePath.c_str(), (int32_t *)&tmp.width, (int32_t *)&tmp.height, nullptr, STBI_rgb_alpha);
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
            std::cout << "failed to load shader file:" << path << std::endl;
            exit(1);
        }
        std::stringstream sstream;
        sstream << file.rdbuf();
        std::string content = sstream.str();
        file.close();

        mTexts[path.data()] = content;

        return mTexts[path.data()];
    }

}