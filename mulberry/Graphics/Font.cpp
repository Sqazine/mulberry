#include "Font.h"
#include "Core/Logger.h"
namespace mulberry
{
    Font::Font()
    {
    }
    Font::~Font()
    {
    }
    bool Font::Load(const std::string &fileName)
    {
        std::vector<int> fontSizes = {8, 9,
                                      10, 11, 12, 14, 16, 18,
                                      20, 22, 24, 26, 28,
                                      30, 32, 34, 36, 38,
                                      40, 42, 44, 46, 48,
                                      52, 56,
                                      60, 64, 68,
                                      72};

        for (const auto &size : fontSizes)
        {
            TTF_Font *font = TTF_OpenFont(fileName.c_str(), size);
            if (!font)
            {
                MULBERRY_CORE_ERROR("failed to load font {} in size {}", fileName, size);
                return false;
            }
            mFontData.emplace(size, font);
        }
        return true;
    }

    void Font::UnLoad()
    {
        for (auto &font : mFontData)
            TTF_CloseFont(font.second);
    }

    std::unique_ptr<Texture> Font::RenderText(const std::string &text, const Color &color, int32_t pointSize)
    {
        std::unique_ptr<Texture> texture = nullptr;
        SDL_Color sdlColor;
        sdlColor.r = static_cast<uint8_t>(color.r * 255);
        sdlColor.g = static_cast<uint8_t>(color.g * 255);
        sdlColor.b = static_cast<uint8_t>(color.b * 255);
        sdlColor.a = static_cast<uint8_t>(color.a * 255);

        auto iter = mFontData.find(pointSize);
        if (iter != mFontData.end())
        {
            TTF_Font *font = iter->second;
            SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), sdlColor);
            if (surf != nullptr)
            {
                texture = std::make_unique<Texture>();
                texture->CreateFromSurface(surf);
                SDL_FreeSurface(surf);
            }
        }
        else
            MULBERRY_CORE_ERROR("Points size %d is unsupported", pointSize);
        return std::move(texture);
    }
}