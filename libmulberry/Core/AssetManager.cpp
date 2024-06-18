

#include "AssetManager.h"
#include "Graphics/RHI/Texture.h"
#include <stb/stb_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Logger.h"
#include "Platform/Utils.h"
namespace mulberry
{
    AssetManager::AssetManager()
    {
    }

    AssetManager::~AssetManager()
    {
    }

    const ImageData &AssetManager::LoadImageData(const std::string &filePath)
    {
        auto iter = mImageDatas.find(filePath);
        if (iter != mImageDatas.end())
            return iter->second;

        int32_t channel;

        ImageData tmp;
        stbi_set_flip_vertically_on_load(true);
        uint8_t *data = stbi_load(filePath.c_str(), (int32_t *)&tmp.width, (int32_t *)&tmp.height, &channel, STBI_default);
        tmp.pixels = std::vector<uint8_t>(data, data + (tmp.width * tmp.height * 4));

        if (channel == 4)
            tmp.format = Format::R8G8B8A8_UNORM;
        else if (channel == 3)
            tmp.format = Format::R8G8B8_UNORM;

        mImageDatas[filePath] = tmp;
        return mImageDatas[filePath];
    }

    const std::string &AssetManager::LoadText(std::string_view path)
    {
        auto iter = mTexts.find(path.data());
        if (iter != mTexts.end())
            return iter->second;

        std::ifstream file(path.data(), std::ios::binary);
        if (!file.is_open())
            MULBERRY_CORE_ERROR("failed to load text:{}\n");
        std::stringstream sstream;
        sstream << file.rdbuf();
        std::string content = sstream.str();
        file.close();

        mTexts[path.data()] = IO::LoadText(path);

        return mTexts[path.data()];
    }

}