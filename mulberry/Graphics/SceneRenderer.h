#pragma once
#include <cstdint>
#include <memory>
#include "Graphics/PrimitiveGeometry.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include "Scene/Component/RenderComponent.h"
#include "Scene/Component/SpriteComponent.h"
#include "Scene/Component/CameraComponent.h"
#include "Pipeline.h"
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
		void RenderAuxiliary(const Entity *entity, CameraComponent *camera,const PrimitiveGeometry& primitive);

		std::unique_ptr<class GizmoMaterial> mGizmoMaterial;

		std::unique_ptr<PrimitiveGeometry> mLinePrimitive;
		std::unique_ptr<PrimitiveGeometry> mSpritePrimitive;
		std::unique_ptr<PrimitiveGeometry> mQuadPrimitive;
		std::unique_ptr<PrimitiveGeometry> mCirclePrimitive;

		std::unique_ptr<rhi::RasterPipeline> mSpriteRasterPipeline;
		std::unique_ptr<rhi::RasterPipeline> mAuxiliaryRasterPipeline;
		std::unique_ptr<rhi::RasterPipeline> mPointRasterPipeline;
	};
}