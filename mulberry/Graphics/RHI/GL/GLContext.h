#pragma once
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <string_view>
#include <mutex>
#include "Vec2.h"
#include "Math/Color.h"
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include "Platform/SDL2/GLContextImpl.h"
#else
#endif

namespace mulberry
{
	class GLContext
	{
	public:
		GLContext();
		~GLContext();

		void Init();

		Vec2 GetVersion();

		void SetClearColor(const Color &clearColor);
		void IsClearColorBuffer(bool isClear);
		void BeginFrame();
		void EndFrame();

	private:
		std::unique_ptr<class GLRasterPass> mDefaultRasterPass;
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		SDL2GLContextImpl mSDL2GLContextImpl;
#else
#error "Unknown platform GLContext"
#endif
	};
}