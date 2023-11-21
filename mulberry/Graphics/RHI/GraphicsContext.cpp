#include "GraphicsContext.h"
#include "App.h"
#include "GL/GLContext.h"
#include "VK/VKContext.h"
#include "Math/Color.h"
namespace mulberry
{
	GraphicsContext::GraphicsContext()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			mGLContext = std::make_unique<GLContext>();
			break;
		default:
			mVKContext = std::make_unique<VKContext>();
			break;
		}
	}

	GraphicsContext::~GraphicsContext()
	{
	}

	void GraphicsContext::Init()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			mGLContext->Init();
			break;
		default:
			mVKContext->Init();
			break;
		}
	}

	void GraphicsContext::SetClearColor(const Color &clearColor)
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			mGLContext->SetClearColor(clearColor);
			break;
		default:
			mVKContext->SetClearColor(clearColor);
			break;
		}
	}
	void GraphicsContext::IsClearColorBuffer(bool isClear)
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			mGLContext->IsClearColorBuffer(isClear);
			break;
		default:
			mVKContext->IsClearColorBuffer(isClear);
			break;
		}
	}

	void GraphicsContext::BeginFrame()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			mGLContext->BeginFrame();
			break;
		default:
			mVKContext->BeginFrame();
			break;
		}
	}
	void GraphicsContext::EndFrame()
	{
		switch (App::GetInstance().GetGraphicsConfig().backend)
		{
		case GraphicsBackend::GL:
			mGLContext->EndFrame();
			break;
		default:
			mVKContext->EndFrame();
			break;
		}
	}

	GLContext *GraphicsContext::GetGLContext() const
	{
		return mGLContext.get();
	}

	VKContext *GraphicsContext::GetVKContext() const
	{
		return mVKContext.get();
	}
}