#include "SpriteComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
namespace Pe2
{

	COMPONENT_DEFINITION(Component, SpriteComponent)

	SpriteComponent::SpriteComponent()
		: Component()
	{
	}

	SpriteComponent::~SpriteComponent()
	{
	}

	const Texture* SpriteComponent::GetTexture() const
	{
		return m_Texture.get();
	}

	void SpriteComponent::DefineRequiredComponents()
	{
		REQUIRED_COMPONENT(TransformComponent)
	}

}