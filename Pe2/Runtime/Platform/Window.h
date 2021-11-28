#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "../Math/Vec2.h"
struct WindowInfo
{
    std::string title;
    Vec2 extent;
    bool resizeable = true;
    bool fullScreen = false;
};

class Window
{
public:
    Window(const WindowInfo &info);
    SDL_Window *GetHandle() const;

        
private:
    SDL_Window *m_WindowHandle;
};