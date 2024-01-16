#pragma once
#include "Component.h"
#include <memory>
#include "Graphics/Material.h"
#include "Graphics/RHI/Texture.h"
namespace mulberry
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent();
		~RenderComponent();

		void Init() override;
	protected:

		friend class SceneRenderer;

		void SetMaterial(RasterMaterial *mat);
		const RasterMaterial *GetMaterial() const;
		std::unique_ptr<RasterMaterial> material;
	};
}