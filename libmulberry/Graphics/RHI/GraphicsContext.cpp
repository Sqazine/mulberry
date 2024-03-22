#include "GraphicsContext.h"
#include "App.h"
#include "Utils.h"
#include "Graphics/RHI/VK/GraphicsContext.h"
#include "Color.h"
namespace mulberry::rhi
{
	GraphicsContext::GraphicsContext()
	{
	}

	GraphicsContext::~GraphicsContext()
	{
	}

	void GraphicsContext::Init()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->Init());
		mDefaultGraphicsPass = std::make_unique<GraphicsPass>();
	}

	void GraphicsContext::Destroy()
	{
		mDefaultGraphicsPass.reset(nullptr);
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->Destroy());
	}

	GraphicsPass *GraphicsContext::GetDefaultDrawPass()
	{
		return mDefaultGraphicsPass.get();
	}

	void GraphicsContext::BeginFrame()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->BeginFrame())
		mDefaultGraphicsPass->Begin();
	}

	void GraphicsContext::EndFrame()
	{
		mDefaultGraphicsPass->End();
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->EndFrame());
	}
}