#pragma once
#include <memory>
#include <mutex>
#include "Vec2.h"
#include "GraphicsConfig.h"
#include "Graphics/RHI/VK/GRaphicsContext.h"
namespace mulberry::rhi
{
	class GraphicsContext
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		void Init();

		void SetClearColor(const struct Color &clearColor);
		void IsClearColorBuffer(bool isClear);

		void BeginFrame();
		void EndFrame();

		vk::GraphicsContext* GetVKGraphicsContextImpl() const;
	private:
		std::unique_ptr<vk::GraphicsContext> mVKContextImpl;
	};
}