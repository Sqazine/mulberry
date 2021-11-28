#pragma once
#include <SDL2/SDL.h>
#include "RenderContextInfo.h"
namespace Pe2
{
	class RenderContext
	{
	public:
		~RenderContext();

		static void CreateRenderContext(const RenderContextInfo &config);

		static void DestroyRenderContext();

		static void SwapWindow();

		static const RenderBackend &GetRenderBackend();

		static SDL_Window *GetWindow();

	private:
		RenderContext();

		static RenderBackend m_RenderBackend;
	};
}