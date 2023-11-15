#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "GLContextImpl.h"
#include "WindowImpl.h"
#include "App.h"
#include "Core/Logger.h"
namespace mulberry
{
	void SDL2GLContextImpl::Init()
	{
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

		if (App::GetInstance().GetGraphicsConfig().useDoubleBuffer)
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		else
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

		mContextHandle = SDL_GL_CreateContext(((SDL2WindowImpl*)App::GetInstance().GetWindow())->GetHandle());
	
		if (!mContextHandle)
			MULBERRY_CORE_ERROR("Failed to create SDL opengl context:{}", SDL_GetError());
		
		SDL_GL_SetSwapInterval((App::GetInstance().GetGraphicsConfig().useVSync ? 1 : 0));

		if (!gladLoadGL())
			MULBERRY_CORE_ERROR("Failed to load GLAD:{}", glGetError());

		int num;
		glGetIntegerv(GL_NUM_EXTENSIONS, &num);
		for (size_t i = 0; i < num; ++i)
			mExtensions.emplace_back((const char *)glGetStringi(GL_EXTENSIONS, i));

		MULBERRY_CORE_INFO("OpenGL Info:");
		MULBERRY_CORE_INFO("Vendor:{}", glGetString(GL_VENDOR));
		MULBERRY_CORE_INFO("Renderer:{}", glGetString(GL_RENDERER));
		MULBERRY_CORE_INFO("Version:{}", glGetString(GL_VERSION));

		std::string output;
		for (size_t i = 0; i < mExtensions.size(); ++i)
			output += "\t\t\t" + std::string(mExtensions[i]) + "\n";

		MULBERRY_CORE_INFO("Extensions:\n{}", output.c_str());
	}

	void SDL2GLContextImpl::Destroy()
	{
		SDL_GL_DeleteContext(mContextHandle);
	}

	Vec2 SDL2GLContextImpl::GetVersion()
	{
		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		return Vec2(major, minor);
	}

	void SDL2GLContextImpl::BeginFrame()
	{
	}

	void SDL2GLContextImpl::EndFrame()
	{
		SDL_GL_SwapWindow(((SDL2WindowImpl*)App::GetInstance().GetWindow())->GetHandle());
	}
}
