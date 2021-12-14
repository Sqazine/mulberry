#pragma once
#include <cstdint>
#include <memory>
#include "IndexBuffer.h"
#include <glad/glad.h>
#include "Primitive.h"
#include "Shader.h"
#include "../Scene/Entity.h"
#include "../Scene/Scene.h"
#include "../Scene/Component/SpriteComponent.h"
#include "../Scene/Component/CameraComponent.h"
namespace Pe2
{

	class SceneRenderer
	{
	public:
		void Init();
		void Render(const Scene *scene);
	private:
		void RenderSprite(const Entity *entity);
		void RenderLine(const Entity *entity);
		void RenderPoint(const Entity *entity);
		void RenderQuad(const Entity *entity);
		void RenderCircle(const Entity *entity);

		void RenderSpriteInstanced(const std::vector<const Entity *> spriteComps);
		void RenderLineInstances(const std::vector<const Entity *> entities);
		void RenderPointInstanced(const std::vector<const Entity *> entities);
		void RenderQuadInstanced(const std::vector<const Entity *> entities);
		void RenderCircleInstanced(const std::vector<const Entity *> entities);

		std::unique_ptr<ShaderProgram> m_SpriteShaderProgram;
		std::unique_ptr<ShaderProgram> m_GizmoShaderProgram;

		std::unique_ptr<Primitive> m_LinePrimitive;
		std::unique_ptr<Primitive> m_PointPrimitive;
		std::unique_ptr<Primitive> m_QuadPrimitive;
		std::unique_ptr<Primitive> m_CirclePrimitive;
	};

}