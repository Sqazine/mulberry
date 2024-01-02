#pragma once
#include <unordered_map>
#include <SDL_ttf.h>
#include <memory>
#include <string>
#include "Math/Color.h"
#include "Graphics/RHI/Texture.h"
namespace mulberry
{
    class Font
    {
    public:
        Font();
        ~Font();

        bool Load(const std::string &fileName);
        void UnLoad();

        std::unique_ptr<Texture> RenderText(const std::string &text, const Color &color = Color::White, int32_t pointSize = 30);

    private:
        std::unordered_map<int, TTF_Font *> mFontData;
    };
}