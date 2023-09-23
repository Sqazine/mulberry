#pragma once
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <string_view>
#include <mutex>
#include "Singleton.h"
#include "Vec2.h"
#include "Graphics/RHI/GraphicsContext.h"

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include "Platform/SDL2Wrapper/SDL2GLContext.h"
#else
#endif

namespace mulberry
{
	class GLContext : public Singleton<GLContext>
	{
	public:
		void Init();
		void Destroy();

		Vec2 GetVersion();

		void BeginFrame();
		void EndFrame();

	private:
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		SDL2GLContext mSDL2GLContextImpl;
#else
#error "Unknown platform Timer"
#endif
	};
}