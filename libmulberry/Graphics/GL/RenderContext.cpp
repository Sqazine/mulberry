#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "RenderContext.h"
namespace mulberry::GL
{
	RenderContextInfo RenderContext::mRenderCreateInfo;

	SDL_GLContext RenderContext::mRenderContextHandle;

	std::vector<const char *> RenderContext::mExtensions;

	SDL_Window *RenderContext::mWindowHandle = nullptr;

	RenderContext::RenderContext()
	{
	}

	RenderContext::~RenderContext()
	{
	}

	void RenderContext::Init(const RenderContextInfo &config)
	{
		mRenderCreateInfo = config;

		mWindowHandle = SDL_CreateWindow(config.windowInfo.title.c_str(),
										  SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED,
										  config.windowInfo.width,
										  config.windowInfo.height,
										  SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL | config.windowInfo.flags);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_EGL);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		SDL_GL_SetSwapInterval(((config.flags & RENDER_VSYNC) == RENDER_VSYNC ? 1 : 0));
		if ((config.flags & RENDER_DBUFFER) == RENDER_DBUFFER)
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		else
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

		mRenderContextHandle = SDL_GL_CreateContext(mWindowHandle);

		if (!mRenderContextHandle)
			spdlog::error("Failed to create SDL opengl context:{}", SDL_GetError());

		if (!gladLoadGL())
			spdlog::error("Failed to load GLAD:{}", glGetError());

		int num;
		glGetIntegerv(GL_NUM_EXTENSIONS, &num);
		for (size_t i = 0; i < num; ++i)
			mExtensions.emplace_back((const char *)glGetStringi(GL_EXTENSIONS, i));

		spdlog::info("OpenGL Info:");
		spdlog::info("Vendor:{}", glGetString(GL_VENDOR));
		spdlog::info("Renderer:{}", glGetString(GL_RENDERER));
		spdlog::info("Version:{}", glGetString(GL_VERSION));

		std::string output;
		for (size_t i = 0; i < mExtensions.size(); ++i)
			output += "		" + std::string(mExtensions[i]) + "\n";
		spdlog::info("Extensions:\n{}", output.c_str());
	}

	void RenderContext::Destroy()
	{
		SDL_GL_DeleteContext(mRenderContextHandle);
	}

	bool RenderContext::IsSupportExtension(std::string_view extensionName)
	{
		auto iter = std::find_if(mExtensions.begin(), mExtensions.end(), [=](auto &ext)
								 { return ext == extensionName; });
		if (iter == mExtensions.end())
			return false;
		return true;
	}

	bool RenderContext::IsSupportComputeShader()
	{
		return IsSupportExtension("GL_ARB_compute_shader");
	}

	void RenderContext::SwapWindow()
	{
		SDL_GL_SwapWindow(mWindowHandle);
	}

	SDL_GLContext RenderContext::GetRenderContextHandle()
	{
		return mRenderContextHandle;
	}

	SDL_Window *RenderContext::GetWindow()
	{
		return mWindowHandle;
	}

	Vec2 RenderContext::GetVersion()
	{
		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		return Vec2(major, minor);
	}

	Vec2 GetGLSLVersion()
	{
		std::string v = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
		return Vec2(v[0], v[2]);
	}
}