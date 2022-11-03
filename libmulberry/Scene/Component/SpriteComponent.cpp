#include "SpriteComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
namespace mulberry
{

    COMPONENT_DEFINITION(Component, SpriteComponent)

    SpriteComponent::SpriteComponent()
        : RenderComponent()
    {
    }

    SpriteComponent::~SpriteComponent()
    {
    }

    void SpriteComponent::Init()
    {
        RenderComponent::Init();
        material = std::make_unique<SpriteMaterial>();
    }

    void SpriteComponent::SetSprite(GL::Texture *texture)
    {
        ((SpriteMaterial *)material.get())->SetSprite(texture);
    }
    const GL::Texture *SpriteComponent::GetSprite() const
    {
        return ((SpriteMaterial *)material.get())->GetSprite();
    }
}