#include "SpriteComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
namespace mulberry
{
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

    void SpriteComponent::SetSprite(rhi::Texture *texture)
    {
        ((SpriteMaterial *)material.get())->SetSprite(texture);
    }
    const rhi::Texture *SpriteComponent::GetSprite() const
    {
        return ((SpriteMaterial *)material.get())->GetSprite();
    }

    void SpriteComponent::SetTiling(const Vec2 &t)
    {
        ((SpriteMaterial *)material.get())->SetTiling(t);
    }
    const Vec2 &SpriteComponent::GetTiling() const
    {
        return ((SpriteMaterial *)material.get())->GetTiling();
    }

    void SpriteComponent::SetOffset(const Vec2 &o)
    {
         ((SpriteMaterial *)material.get())->SetOffSet(o);
    }
    const Vec2 &SpriteComponent::GetOffset() const
    {
        return  ((SpriteMaterial *)material.get())->GetOffset();
    }
}