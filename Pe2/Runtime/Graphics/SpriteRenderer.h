#pragma once
#include <cstdint>
#include <memory>
#include "IndexBuffer.h"
#include <glad/glad.h>
#include "Quad.h"
namespace Pe2
{

	enum SpriteRenderType
	{
		POINTS = GL_POINTS,
		LINES = GL_LINES,
		TRIANGLES = GL_TRIANGLES,
	};

	class SpriteRenderer
	{
	public:
		static void ClearColorBuffer(float r, float g, float b, float a);

		static void Render(SpriteRenderType mode);
		static void RenderInstanced(SpriteRenderType mode, uint32_t instanceCount);

		private:
		static Quad m_SpriteQuad;
	};

}