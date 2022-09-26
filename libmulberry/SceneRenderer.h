#pragma once
#include <cstdint>
#include <memory>
#include "Graphics/GL/IndexBuffer.h"
#include <glad/glad.h>
#include "Graphics/Primitive.h"
#include "Graphics/GL/Shader.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include "Scene/Component/SpriteComponent.h"
#include "Scene/Component/CameraComponent.h"
namespace mulberry
{

	class SceneRenderer
	{
	public:
		void Init();
		void Render(const Scene *scene);
	private:
		void RenderSprite(const Entity *entity,CameraComponent *camera);
		void RenderLine(const Entity *entity,CameraComponent *camera);
		void RenderPoint(const Entity *entity,CameraComponent *camera);
		void RenderQuad(const Entity *entity,CameraComponent *camera);
		void RenderCircle(const Entity *entity,CameraComponent *camera);

		void RenderSpriteInstanced(const std::vector<const Entity *> spriteComps,CameraComponent *camera);
		void RenderLineInstances(const std::vector<const Entity *> entities,CameraComponent *camera);
		void RenderPointInstanced(const std::vector<const Entity *> entities,CameraComponent *camera);
		void RenderQuadInstanced(const std::vector<const Entity *> entities,CameraComponent *camera);
		void RenderCircleInstanced(const std::vector<const Entity *> entities,CameraComponent *camera);

		std::unique_ptr<GL::ShaderProgram> mSpriteShaderProgram;
		std::unique_ptr<GL::ShaderProgram> mGizmoShaderProgram;

		std::unique_ptr<Primitive> mLinePrimitive;
		std::unique_ptr<Primitive> mPointPrimitive;
		std::unique_ptr<Primitive> mSpritePrimitive;
		std::unique_ptr<Primitive> mQuadPrimitive;
		std::unique_ptr<Primitive> mCirclePrimitive;
	};

}