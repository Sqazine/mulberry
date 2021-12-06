#pragma once
#include <cstdint>
#include <memory>
#include "IndexBuffer.h"
#include <glad/glad.h>
#include "Primitive.h"
namespace Pe2
{

	class SpriteRenderer
	{
	public:
		static void Render();
		static void RenderInstanced(uint32_t instanceCount);

	private:
		static Primitive m_SpritePrimitive;
	};

	class GizmoRenderer
	{
	public:
		static void RenderLine();
		static void RenderPoint();
		static void RenderQuad();
		static void RenderCircle();

	private:
		static Primitive m_LinePrimitive;
		static Primitive m_PointPrimitive;
		static Primitive m_QuadPrimitive;
		static Primitive m_CirclePrimitive;
	};

	class SceneRenderer
	{
	public:
	};

}