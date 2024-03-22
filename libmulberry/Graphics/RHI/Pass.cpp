#include "Pass.h"
#include "App.h"
namespace mulberry::rhi
{
	SwapChainPass::SwapChainPass()
	{
	}

	SwapChainPass::~SwapChainPass()
	{
	}

	void SwapChainPass::SetClearColor(const Color &clearColor)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetClearColor(clearColor));
	}
	void SwapChainPass::IsClearColorBuffer(bool isClear)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->IsClearColorBuffer(isClear));
	}

	void SwapChainPass::SetViewport(const Viewport &viewport)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetViewport(viewport));
	}

	void SwapChainPass::SetPipeline(const GraphicsPipeline &pipeline)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetPipeline(pipeline.GetVkImpl()));
	}

	void SwapChainPass::Begin()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->Begin());
	}

	void SwapChainPass::End()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->End());
	}
}