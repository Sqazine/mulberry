#pragma once
#include "Component.h"
#include <memory>
#include "../../Render/Texture.h"
namespace Pe2
{
	class SpriteComponent : public Component
	{
		COMPONENT_DECLARATION()
	public:
		SpriteComponent();
		~SpriteComponent();

		const Texture* GetTexture() const;

	protected:
		friend class Entity;
		void DefineRequiredComponents() override;

	private:
		std::unique_ptr<Texture> m_Texture;
	};

}