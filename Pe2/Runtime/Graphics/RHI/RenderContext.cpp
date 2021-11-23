#include "RenderContext.h"
#include "GL/Context.h"
#include "VK/Context.h"
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

	switch (m_RenderBackend)
	{
	case RenderBackend::VK:
		VK::Context::CreateContext(config);
		break;
	default:
		GL::Context::CreateContext(config);
		break;
	}
}

void RenderContext::DestroyRenderContext()
{
	switch (m_RenderBackend)
	{
	case RenderBackend::VK:
		VK::Context::DestroyContext();
		break;
	default:
		GL::Context::DestroyContext();
		break;
	}
}

void RenderContext::SwapWindow()
{
	switch (m_RenderBackend)
	{
	case RenderBackend::VK:
		break;
	default:
		GL::Context::SwapWindow();
		break;
	}
}

const RenderBackend &RenderContext::GetRenderBackend()
{
	return m_RenderBackend;
}

SDL_Window *RenderContext::GetWindowHandle()
{
	switch (m_RenderBackend)
	{
	case RenderBackend::VK:
		VK::Context::GetWindowHandle();
		break;
	default:
		GL::Context::GetWindowHandle();
		break;
	}
}