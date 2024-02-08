#include "GraphicsContext.h"
#include "App.h"
#include "Utils.h"
#include "Graphics/RHI/VK/Context.h"
#include "Color.h"
namespace mulberry::rhi
{
	GraphicsContext::GraphicsContext()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKContextImpl = std::make_unique<vk::Context>())
	}

	GraphicsContext::~GraphicsContext()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKContextImpl.reset(nullptr));
	}

	void GraphicsContext::Init()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKContextImpl->Init());
	}

	void GraphicsContext::SetClearColor(const Color &clearColor)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKContextImpl->SetClearColor(clearColor));
	}
	
	void GraphicsContext::IsClearColorBuffer(bool isClear)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKContextImpl->IsClearColorBuffer(isClear));
	}

	void GraphicsContext::BeginFrame()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKContextImpl->BeginFrame())
	}
	void GraphicsContext::EndFrame()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKContextImpl->EndFrame())
	}

	vk::Context *GraphicsContext::GetVKContextImpl() const
	{
		return mVKContextImpl.get();
	}
}