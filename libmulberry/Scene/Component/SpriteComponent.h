#pragma once
#include "Component.h"
#include <memory>
#include "Graphics/RenderMaterial.h"
#include "../../Graphics/GL/Texture.h"
namespace mulberry
{
	class SpriteComponent : public Component
	{
		COMPONENT_DECLARATION()
	public:
		SpriteComponent();
		~SpriteComponent();

		void Init() override;

		std::unique_ptr<RenderMaterial> material;
	};

}