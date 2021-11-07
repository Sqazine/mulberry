#include "Context.h"
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "Context.h"
namespace GL
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

	void Context::CreateContext(const RenderContextCreateInfo &config)
	{
		m_RenderCreateInfo = config;
	}

	void Context::InitContext(SDL_Window *window)
	{
		m_WindowHandle = window;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		if (m_RenderCreateInfo.apiVersion != RENDER_API_NEWEST)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GET_API_VERSION_MAJOR(m_RenderCreateInfo.apiVersion));
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GET_API_VERSION_MINOR(m_RenderCreateInfo.apiVersion));
		}

		m_ContextHandle = SDL_GL_CreateContext(window);

		if (!m_ContextHandle)
			spdlog::error("failed to create SDL opengl context:{}", SDL_GetError());

		if (!gladLoadGL())
			spdlog::error("failed to load GLAD:{}", glGetError());

		//垂直同步
		int success = SDL_GL_SetSwapInterval((m_RenderCreateInfo.useVSync ? 1 : 0));
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

	void Context::DestroyContext()
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
}