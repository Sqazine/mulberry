#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "../Math/Vec2.h"
struct WindowCreateInfo
{
    std::string title;
    Vec2 extent;
    bool resizeable = true;
    bool fullScreen = false;
};

class Window
{
public:
    Window(const WindowCreateInfo &info);
    SDL_Window *GetHandle() const;

        
private:
    SDL_Window *m_WindowHandle;
};