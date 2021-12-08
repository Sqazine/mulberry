#pragma once
#include <unordered_map>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "../Math/Color.h"
#include "Texture.h"
namespace Pe2
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
        std::unordered_map<int, TTF_Font *> m_FontData;
    };
}