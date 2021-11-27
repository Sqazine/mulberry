#include "Context.h"
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "Context.h"
namespace Pe2::GL
{
	RenderContextCreateInfo Context::m_RenderCreateInfo;

	SDL_GLContext Context::m_ContextHandle;

	SDL_Window *Context::m_WindowHandle = nullptr;

	Context::Context()
	{
	}

	Context::~Context()
	{
	}

	void Context::Init(const RenderContextCreateInfo &config)
	{
		m_RenderCreateInfo = config;

		uint32_t windowFlag = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL;
		if (config.windowCreateInfo.resizeable)
			windowFlag |= SDL_WINDOW_RESIZABLE;

		m_WindowHandle = SDL_CreateWindow(config.windowCreateInfo.title.c_str(),
										  SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED,
										  config.windowCreateInfo.extent.x,
										  config.windowCreateInfo.extent.y,
										  windowFlag);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		m_ContextHandle = SDL_GL_CreateContext(m_WindowHandle);

		if (!m_ContextHandle)
			spdlog::error("failed to create SDL opengl context:{}", SDL_GetError());

		if (!gladLoadGL())
			spdlog::error("failed to load GLAD:{}", glGetError());

		//垂直同步
		int success = SDL_GL_SetSwapInterval(((m_RenderCreateInfo.flag&DOUBLE_BUFFERING)==DOUBLE_BUFFERING ? 1 : 0));
		if (success == -1)
			spdlog::error("failed to open/close opengl VSync:{}", SDL_GetError());
		{
			spdlog::info("OpenGL Info:\n");
			spdlog::info("Vendor:{}", glGetString(GL_VENDOR));
			spdlog::info("Renderer:{}", glGetString(GL_RENDERER));
			spdlog::info("Version:{}", glGetString(GL_VERSION));
			spdlog::info("Extensions:{}", glGetString(GL_EXTENSIONS));
		}
	}

	void Context::Destroy()
	{
		SDL_GL_DeleteContext(m_ContextHandle);
	}

	bool Context::IsSupportExtension(std::string_view extensionName)
	{
		return SDL_GL_ExtensionSupported(extensionName.data());
	}

	void Context::SwapWindow()
	{
		SDL_GL_SwapWindow(m_WindowHandle);
	}

	SDL_GLContext Context::GetContextHandle()
	{
		return m_ContextHandle;
	}

	SDL_Window *Context::GetWindow()
	{
		return m_WindowHandle;
	}
}