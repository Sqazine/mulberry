#include "Pass.h"
#include "App.h"
namespace mulberry
{
	SwapChainPass::SwapChainPass()
	{
	}

	SwapChainPass::~SwapChainPass()
	{
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

	 ColorAttachment* SwapChainPass::GetColorAttachment() const
	 {
		GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->GetColorAttachment());
	 }
}