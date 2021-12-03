#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "RenderContext.h"
namespace Pe2
{
	RenderContextInfo RenderContext::m_RenderCreateInfo;

	SDL_GLContext RenderContext::m_RenderContextHandle;

	SDL_Window *RenderContext::m_WindowHandle = nullptr;

	RenderContext::RenderContext()
	{
	}

	RenderContext::~RenderContext()
	{
	}

	void RenderContext::Init(const RenderContextInfo &config)
	{
		m_RenderCreateInfo = config;

		uint32_t windowFlag = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL;
		if (config.windowInfo.resizeable)
			windowFlag |= SDL_WINDOW_RESIZABLE;

		m_WindowHandle = SDL_CreateWindow(config.windowInfo.title.c_str(),
										  SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED,
										  config.windowInfo.width,
										  config.windowInfo.height,
										  windowFlag);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		m_RenderContextHandle = SDL_GL_CreateContext(m_WindowHandle);

		if (!m_RenderContextHandle)
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

	void RenderContext::Destroy()
	{
		SDL_GL_DeleteContext(m_RenderContextHandle);
	}

	bool RenderContext::IsSupportExtension(std::string_view extensionName)
	{
		return SDL_GL_ExtensionSupported(extensionName.data());
	}

	void RenderContext::SwapWindow()
	{
		SDL_GL_SwapWindow(m_WindowHandle);
	}

	SDL_GLContext RenderContext::GetRenderContextHandle()
	{
		return m_RenderContextHandle;
	}

	SDL_Window *RenderContext::GetWindow()
	{
		return m_WindowHandle;
	}
}