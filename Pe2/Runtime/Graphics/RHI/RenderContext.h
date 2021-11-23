#pragma once
#include <SDL2/SDL.h>
#include "RenderContextCreateInfo.h"
class RenderContext
{
public:
	~RenderContext();

	static void CreateRenderContext(const RenderContextCreateInfo& config);

	static void DestroyRenderContext();

	static void SwapWindow();

	static const RenderBackend& GetRenderBackend();

	static SDL_Window* GetWindowHandle();
private:
	RenderContext();
	
	static RenderBackend m_RenderBackend;
};
