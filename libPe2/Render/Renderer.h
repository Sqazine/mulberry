#pragma once
#include <cstdint>
#include <memory>
#include "IndexBuffer.h"
#include <glad/glad.h>
#include "Primitive.h"
#include "../Scene/Entity.h"
#include "../Scene/Scene.h"
namespace Pe2
{

	class SpriteRenderer
	{
	public:
		static void Render(const Entity *entity);
		static void RenderInstanced(const std::vector<Entity *> entities);

	private:
		static Primitive m_SpritePrimitive;
	};

	class GizmoRenderer
	{
	public:
		static void RenderLine(const Entity *entity);
		static void RenderPoint(const Entity *entity);
		static void RenderQuad(const Entity *entity);
		static void RenderCircle(const Entity *entity);

		static void RenderLineInstances(const std::vector<Entity *> entities);
		static void RenderPointInstanced(const std::vector<Entity *> entities);
		static void RenderQuadInstanced(const std::vector<Entity *> entities);
		static void RenderCircleInstanced(const std::vector<Entity *> entities);

	private:
		static Primitive m_LinePrimitive;
		static Primitive m_PointPrimitive;
		static Primitive m_QuadPrimitive;
		static Primitive m_CirclePrimitive;
	};

	class SceneRenderer
	{
	public:
		void RenderGizmo(const Scene *scene);
		void Render(const Scene *scene);
		void RenderUI(const Scene *scene);
	};

}