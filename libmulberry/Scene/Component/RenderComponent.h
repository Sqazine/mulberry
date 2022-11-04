#pragma once
#include "Component.h"
#include <memory>
#include "Graphics/RenderMaterial.h"
#include "Graphics/GL/Texture.h"
namespace mulberry
{
	class RenderComponent : public Component
	{
		COMPONENT_DECLARATION()
	public:
		RenderComponent();
		~RenderComponent();

		void Init() override;

	protected:

		friend class SceneRenderer;

		void SetMaterial(RenderMaterial *mat);
		const RenderMaterial *GetMaterial() const;
		std::unique_ptr<RenderMaterial> material;
	};
}