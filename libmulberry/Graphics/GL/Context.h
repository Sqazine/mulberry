#pragma once
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <string_view>
#include <mutex>
#include "Singleton.h"
#include "Vec2.h"
#include "Graphics/GraphicsContext.h"

namespace mulberry::gl
{
	class Context : public Singleton<gl::Context>
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