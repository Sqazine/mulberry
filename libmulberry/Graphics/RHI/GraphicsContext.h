#pragma once
#include <memory>
#include <mutex>
#include "Defs.h"
#include "Vec2.h"
#include "GraphicsConfig.h"
#include "Graphics/RHI/VK/GraphicsContext.h"
namespace mulberry
{
	class GraphicsContext : GRAPHICS_RHI_IMPL_DECL(GraphicsContext)
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		void Init();

		class SwapChainPass *GetSwapChainPass();

	private:
		std::unique_ptr<class SwapChainPass> mSwapChainPass;
	};
}