#include "Pass.h"
#include "App.h"
namespace mulberry::rhi
{
	GraphicsPass::GraphicsPass()
	{
	}

	GraphicsPass::~GraphicsPass()
	{
	}

	void GraphicsPass::SetClearColor(const Color &clearColor)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetClearColor(clearColor));
	}
	void GraphicsPass::IsClearColorBuffer(bool isClear)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->IsClearColorBuffer(isClear));
	}

	void GraphicsPass::SetViewport(const Viewport &viewport)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetViewport(viewport));
	}

	void GraphicsPass::SetPipeline(const GraphicsPipeline &pipeline)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetPipeline(pipeline.GetVkImpl()));
	}

	void GraphicsPass::Begin()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->Begin());
	}

	void GraphicsPass::End()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->End());
	}
}