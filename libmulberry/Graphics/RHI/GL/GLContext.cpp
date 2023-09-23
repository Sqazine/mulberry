#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "RHI/GraphicsContext.h"
#include "GLContext.h"
#include "App.h"
namespace mulberry
{
	void GLContext::Init()
	{
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		mSDL2GLContextImpl.Init();
#else
#error "Unknown platform GLContext"
#endif
	}

	void GLContext::Destroy()
	{
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		mSDL2GLContextImpl.Destroy();
#else
#error "Unknown platform GLContext"
#endif
	}

	Vec2 GLContext::GetVersion()
	{
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		return mSDL2GLContextImpl.GetVersion();
#else
#error "Unknown platform GLContext"
#endif
	}

	void GLContext::BeginFrame()
	{
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		mSDL2GLContextImpl.BeginFrame();
#else
#error "Unknown platform GLContext"
#endif
	}

	void GLContext::EndFrame()
	{
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		mSDL2GLContextImpl.EndFrame();
#else
#error "Unknown platform GLContext"
#endif
	}
}
