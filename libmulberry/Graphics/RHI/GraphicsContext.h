#pragma once
#include <memory>
#include <mutex>
#include "Vec2.h"
#include "GraphicsConfig.h"
#include "Graphics/RHI/GL/GLContext.h"
#include "Graphics/RHI/VK/VKContext.h"
namespace mulberry
{
	class GraphicsContext
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		void Init();

		void SetClearColor(const class Color &clearColor);
		void IsClearColorBuffer(bool isClear);

		void BeginFrame();
		void EndFrame();

		GLContext* GetGLContext() const;
		VKContext* GetVKContext() const;

	private:
		std::unique_ptr<GLContext> mGLContext;
		std::unique_ptr<VKContext> mVKContext;
	};
}