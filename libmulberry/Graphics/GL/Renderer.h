#pragma once
#include <cstdint>
#include <memory>
#include <glad/glad.h>
#include <array>
#include "IndexBuffer.h"

namespace mulberry::gl
{

	enum RenderType
	{
		POINTS = GL_POINTS,
		LINES = GL_LINES,
		LINE_STRIP = GL_LINE_STRIP,
		LINE_LOOP = GL_LINE_LOOP,
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
	};

	enum CullType
	{
		NONE,
		FRONT,

	};

	class Renderer
	{
	public:

		static std::array<int32_t,4> GetCurViewportInfo();
		static void SetViewport(const std::array<int32_t,4>& info);
		static void SetViewport(int32_t x,int32_t y,int32_t width,int32_t height);

		static void ClearColorBuffer(float r, float g, float b, float a);

		static void EnableDepthTest(bool active);
		static void EnableCullFace(bool active);

		static void Render(const IndexBuffer* ibo, RenderType mode);
		static void RenderInstanced(const IndexBuffer* ibo, RenderType mode, uint32_t instanceCount);
	};

}