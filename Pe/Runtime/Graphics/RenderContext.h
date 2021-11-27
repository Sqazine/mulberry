#pragma once
#include <SDL2/SDL.h>
#include "RenderContextCreateInfo.h"
namespace Pe2
{
	class RenderContext
	{
	public:
		~RenderContext();

		static void CreateRenderContext(const RenderContextCreateInfo &config);

		static void DestroyRenderContext();

		static void SwapWindow();

		static const RenderBackend &GetRenderBackend();

		static SDL_Window *GetWindow();

	private:
		RenderContext();

		static RenderBackend m_RenderBackend;
	};
}