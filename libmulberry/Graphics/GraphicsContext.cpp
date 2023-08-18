#include "GraphicsContext.h"
#include "App.h"
#include "GL/GLContext.h"
#include "VK/VKContext.h"
namespace mulberry
{
	void GraphicsContext::Init()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			GLContext::GetInstance().Init();
			break;
		default:
			VKContext::GetInstance().Init();
			break;
		}
	}
	void GraphicsContext::Destroy()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			GLContext::GetInstance().Destroy();
			break;
		default:
			VKContext::GetInstance().Destroy();
			break;
		}
	}

	void GraphicsContext::BeginFrame()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			GLContext::GetInstance().BeginFrame();
			break;
		default:
			VKContext::GetInstance().BeginFrame();
			break;
		}
	}
	void GraphicsContext::EndFrame()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			GLContext::GetInstance().EndFrame();
			break;
		default:
			VKContext::GetInstance().EndFrame();
			break;
		}
	}
}