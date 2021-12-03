

#include "ResourceManager.h"
#include "../Graphics/Texture.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
namespace Pe2
{
    ResourceManager::ResourceManager()
    {
    }

    ResourceManager::~ResourceManager()
    {
    }

    const ImgData &ResourceManager::LoadImgData(const std::string &filePath)
    {
        auto iter = m_ImgDatas.find(filePath);
        if (iter != m_ImgDatas.end())
            return iter->second;
        ImgData tmp;
        uint8_t *data = stbi_load(filePath.c_str(), (int32_t *)&tmp.width, (int32_t *)&tmp.height, nullptr, STBI_rgb_alpha);
        tmp.pixels = std::vector<uint8_t>(data, data + (tmp.width * tmp.height * 4));
        m_ImgDatas[filePath] = tmp;
        return m_ImgDatas[filePath];
    }

    const std::string &ResourceManager::LoadText(std::string_view path)
    {
        auto iter = m_Texts.find(path.data());
        if (iter != m_Texts.end())
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

        m_Texts[path.data()] = content;

        return m_Texts[path.data()];
    }

}