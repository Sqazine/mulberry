#pragma once
#include <cstdint>
#include <memory>
#include "Graphics/RHI/GL/GLIndexBuffer.h"
#include <glad/glad.h>
#include "Graphics/Primitive.h"
#include "Graphics/RHI/GL/GLShader.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include "Scene/Component/RenderComponent.h"
#include "Scene/Component/SpriteComponent.h"
#include "Scene/Component/CameraComponent.h"
#include "RasterPipeline.h"
#include "RasterPass.h"
namespace mulberry
{
	class SceneRenderer
	{
	public:
		void Init();
		void Render(const Scene *scene);

	private:
		void RenderSprite(const Entity *entity, CameraComponent *camera);
		void RenderAuxiliary(const Entity *entity, CameraComponent *camera,const Primitive& primitive);

		std::unique_ptr<class GizmoMaterial> mGizmoMaterial;

		std::unique_ptr<Primitive> mLinePrimitive;
		std::unique_ptr<Primitive> mSpritePrimitive;
		std::unique_ptr<Primitive> mQuadPrimitive;
		std::unique_ptr<Primitive> mCirclePrimitive;

		std::unique_ptr<RasterPipeline> mSpriteRasterPipeline;
		std::unique_ptr<RasterPipeline> mAuxiliaryRasterPipeline;
		std::unique_ptr<RasterPipeline> mPointRasterPipeline;
	};
}