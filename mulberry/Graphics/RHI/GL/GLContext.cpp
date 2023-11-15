#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "RHI/GraphicsContext.h"
#include "GLContext.h"
#include "GLDrawPass.h"
#include "App.h"
namespace mulberry
{
	GLContext::GLContext()
	{
	}

	GLContext::~GLContext()
	{
		mDefaultDrawPass.reset(nullptr);

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		mSDL2GLContextImpl.Destroy();
#else
#error "Unknown platform GLContext"
#endif
	}

	void GLContext::Init()
	{
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		mSDL2GLContextImpl.Init();
#else
#error "Unknown platform GLContext"
#endif

		mDefaultDrawPass = std::make_unique<GLDrawPass>();
	}

	Vec2 GLContext::GetVersion()
	{
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		return mSDL2GLContextImpl.GetVersion();
#else
#error "Unknown platform GLContext"
#endif
	}

	void GLContext::SetClearColor(const Color &clearColor)
	{
		mDefaultDrawPass->SetClearColor(clearColor);
	}
	void GLContext::IsClearColorBuffer(bool isClear)
	{
		mDefaultDrawPass->IsClearColorBuffer(isClear);
	}

	void GLContext::BeginFrame()
	{
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		mSDL2GLContextImpl.BeginFrame();
#else
#error "Unknown platform GLContext"
#endif
		mDefaultDrawPass->Begin();
	}

	void GLContext::EndFrame()
	{
		mDefaultDrawPass->End();

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		mSDL2GLContextImpl.EndFrame();
#else
#error "Unknown platform GLContext"
#endif
	}
}
