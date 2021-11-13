#include "RenderContext.h"

RenderBackend RenderContext::m_RenderBackend;

RenderContext::RenderContext()
{
}
RenderContext::~RenderContext()
{
}

void RenderContext::CreateRenderContext(const RenderContextCreateInfo &config)
{
	m_RenderBackend = config.backend;
	if (m_RenderBackend == RENDER_BACKEND_GL)
		GL::Context::CreateContext(config);
	else
		VK::Context::CreateContext(config);
}

void RenderContext::InitRenderContext(SDL_Window *window)
{
	switch (m_RenderBackend)
	{
	case RENDER_BACKEND_GL:
		GL::Context::InitContext(window);
		break;
	default:
		VK::Context::InitContext(window);
		break;
	}
}
void RenderContext::DestroyRenderContext()
{
	switch (m_RenderBackend)
	{
	case RENDER_BACKEND_GL:
		GL::Context::DestroyContext();
		break;
	default:
		VK::Context::DestroyContext();
		break;
	}
}

void RenderContext::SwapWindow()
{
	switch (m_RenderBackend)
	{
	case RENDER_BACKEND_GL:
		GL::Context::SwapWindow();
		break;
	case RENDER_BACKEND_VK:
		break;
	}
}

const RenderBackend &RenderContext::GetRenderBackend()
{
	return m_RenderBackend;
}
