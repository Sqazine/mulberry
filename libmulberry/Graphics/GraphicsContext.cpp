#include "GraphicsContext.h"
#include "App.h"
#include "GL/Context.h"
#include "VK/Context.h"
namespace mulberry
{
	void GraphicsContext::Init()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			gl::Context::GetInstance().Init();
			break;
		default:
			vk::Context::GetInstance().Init();
			break;
		}
	}
	void GraphicsContext::Destroy()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			gl::Context::GetInstance().Destroy();
			break;
		default:
			vk::Context::GetInstance().Destroy();
			break;
		}
	}

	void GraphicsContext::BeginFrame()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			gl::Context::GetInstance().BeginFrame();
			break;
		default:
			vk::Context::GetInstance().BeginFrame();
			break;
		}
	}
	void GraphicsContext::EndFrame()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			gl::Context::GetInstance().EndFrame();
			break;
		default:
			vk::Context::GetInstance().EndFrame();
			break;
		}
	}
}