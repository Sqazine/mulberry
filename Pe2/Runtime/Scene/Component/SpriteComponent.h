#pragma once
#include "Component.h"
#include <memory>
#include "../../Graphics/Texture.h"
namespace Pe2
{
	class SpriteComponent : public Component
	{
		COMPONENT_DECLARATION()
	public:
		SpriteComponent();
		~SpriteComponent();

	private:
		std::unique_ptr<Texture> m_Texture;
	};

}