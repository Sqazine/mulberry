#pragma once
#include <SDL2/SDL.h>
#include "GLES/Context.h"
#include "VK/Context.h"

class RenderContext
{
public:
	~RenderContext();

	static void CreateRenderContext(const RenderContextCreateInfo& config);

	static void InitRenderContext(SDL_Window* window);
	static void DestroyRenderContext();

	static void SwapWindow();

	static const RenderBackend& GetRenderBackend();

private:
	RenderContext();
	
	static RenderBackend m_RenderBackend;
};
