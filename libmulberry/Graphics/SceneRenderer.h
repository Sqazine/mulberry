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
#include "Pass.h"
namespace mulberry
{
	class SceneRenderer
	{
	public:
		SceneRenderer();
		~SceneRenderer();
		void Render(const Scene *scene);

	private:
		void RenderSprite(SwapChainPass *pass, const Entity *entity, CameraComponent *camera);
		void RenderAuxiliary(SwapChainPass *pass, const Entity *entity, CameraComponent *camera, const PrimitiveGeometry &primitive);

		std::unique_ptr<class GizmoMaterial> mGizmoMaterial;

		std::unique_ptr<PrimitiveGeometry> mLinePrimitive;
		std::unique_ptr<PrimitiveGeometry> mSpritePrimitive;
		std::unique_ptr<PrimitiveGeometry> mQuadPrimitive;
		std::unique_ptr<PrimitiveGeometry> mCirclePrimitive;
	};
}