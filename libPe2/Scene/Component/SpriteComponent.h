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

		void Init() override;

		const Texture* GetTexture() const;
		void SetTexture(Texture* texture);
	private:
		std::unique_ptr<Texture> m_Texture;
	};

}