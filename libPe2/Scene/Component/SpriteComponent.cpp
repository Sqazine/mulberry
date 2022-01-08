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

	void SpriteComponent::Init()
	{
		REQUIRED_COMPONENT(TransformComponent)
	}

	const Texture *SpriteComponent::GetTexture() const
	{
		return m_Texture.get();
	}

	void SpriteComponent::SetTexture(Texture *texture)
	{
		m_Texture.reset(texture);
	}
}