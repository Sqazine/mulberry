#include "RenderContext.h"
#include "GL/Context.h"
#include "VK/Context.h"

namespace Pe2
{

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
			VK::Context::Init(config);
			break;
		default:
			GL::Context::Init(config);
			break;
		}
	}

	void RenderContext::DestroyRenderContext()
	{
		switch (m_RenderBackend)
		{
		case RenderBackend::VK:
			VK::Context::Destroy();
			break;
		default:
			GL::Context::Destroy();
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

	SDL_Window *RenderContext::GetWindow()
	{
		switch (m_RenderBackend)
		{
		case RenderBackend::VK:
			VK::Context::GetWindow();
			break;
		default:
			GL::Context::GetWindow();
			break;
		}
	}
}