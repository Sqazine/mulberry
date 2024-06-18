#include "GraphicsContext.h"
#include "App.h"
#include "Utils.h"
#include "Graphics/RHI/VK/GraphicsContext.h"
#include "Color.h"
namespace mulberry
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
		mSwapChainPass = std::make_unique<SwapChainPass>();
	}

	SwapChainPass *GraphicsContext::GetSwapChainPass()
	{
		return mSwapChainPass.get();
	}
}