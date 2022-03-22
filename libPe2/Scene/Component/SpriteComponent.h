#pragma once
#include "Component.h"
#include <memory>
#include "../../Graphics/GL/Texture.h"
namespace Pe2
{
	class SpriteComponent : public Component
	{
		COMPONENT_DECLARATION()
	public:
		SpriteComponent();
		~SpriteComponent();

		void Init() override;

		const GL::Texture* GetTexture() const;
		void SetTexture(GL::Texture* texture);
	private:
		GL::Texture* mTexture;
	};

}