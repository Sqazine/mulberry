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
		return mTexture.get();
	}

	void SpriteComponent::SetTexture(Texture *texture)
	{
		mTexture.reset(texture);
	}
}