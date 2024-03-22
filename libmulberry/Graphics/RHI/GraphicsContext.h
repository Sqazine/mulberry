#pragma once
#include <memory>
#include <mutex>
#include "Base.h"
#include "Vec2.h"
#include "GraphicsConfig.h"
#include "Graphics/RHI/VK/GraphicsContext.h"
namespace mulberry::rhi
{
	class GraphicsContext : GRAPHICS_RHI_IMPL_DECL(GraphicsContext)
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		void Init();
		void Destroy();

		class SwapChainPass *GetSwapChainPass();

	private:
		std::unique_ptr<class SwapChainPass> mSwapChainPass;
	};
}