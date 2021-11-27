#pragma once
#include <cstdint>
#include <memory>
#include "IndexBuffer.h"
#include <glad/glad.h>

namespace Pe2::GL
{

	enum RenderType
	{
		POINTS = GL_POINTS,
		LINES = GL_LINES,
		TRIANGLES = GL_TRIANGLES,
	};

	class Renderer
	{
	public:
		void ClearColorBuffer(float r, float g, float b, float a);

		void ClearDepthBuffer();
		void ClearStencilBuffer();

		void EnableDepthTest(bool active);
		void EnableCullFace(bool active);

		void Render(const std::shared_ptr<IndexBuffer> &ibo, RenderType mode);
		void Render(uint32_t vertexCount, RenderType mode);
		void RenderInstanced(const std::shared_ptr<IndexBuffer> &ibo, RenderType mode, uint32_t instanceCount);
		void RenderInstanced(uint32_t vertexCount, RenderType mode, uint32_t instanceCount);
	};

}