#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Math/Vec2.h"
namespace mulberry{
class SDL2GLContext
	{
	public:
		void Init();
		void Destroy();

		Vec2 GetVersion();

		void BeginFrame();
		void EndFrame();

	private:
		SDL_GLContext mContextHandle;
		std::vector<const char *> mExtensions;
	};
}