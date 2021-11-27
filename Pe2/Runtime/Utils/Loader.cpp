#include "Loader.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
namespace Pe2::Loader
{

    std::string LoadText(std::string_view path)
    {
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
        return sstream.str();
    }

    ImgData LoadImgDataFromFile(const std::string_view path, bool isFlip)
    {
        ImgData tmp;
        stbi_set_flip_vertically_on_load(isFlip);
        uint8_t *data = stbi_load(path.data(), (int32_t *)&tmp.width, (int32_t *)&tmp.height, nullptr, STBI_rgb_alpha);
        tmp.pixels = std::vector<uint8_t>(data, data + (tmp.width * tmp.height * 4));
        return tmp;
    }
}
