#pragma once
#include "Component.h"
#include <memory>
#include "Graphics/RenderMaterial.h"
#include "Graphics/Texture.h"
#include "RenderComponent.h"
namespace mulberry
{
    class SpriteComponent : public RenderComponent
    {
    public:
        SpriteComponent();
        ~SpriteComponent();

        void Init() override;

        void SetSprite(Texture *texture);
        const Texture *GetSprite() const;

        void SetTiling(const Vec2 &t);
        const Vec2 &GetTiling() const;

        void SetOffset(const Vec2 &o);
        const Vec2 &GetOffset() const;
    };

}