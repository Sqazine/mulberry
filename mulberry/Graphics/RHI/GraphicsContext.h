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

		void BeginFrame();

		class GraphicsPass *GetDefaultDrawPass();
		
		void EndFrame();

	private:
		std::unique_ptr<class GraphicsPass> mDefaultGraphicsPass;
	};
}