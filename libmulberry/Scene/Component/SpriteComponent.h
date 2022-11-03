#pragma once
#include "Component.h"
#include <memory>
#include "Graphics/RenderMaterial.h"
#include "Graphics/GL/Texture.h"
#include "RenderComponent.h"
namespace mulberry
{
    class SpriteComponent : public RenderComponent
    {
        COMPONENT_DECLARATION()
    public:
        SpriteComponent();
        ~SpriteComponent();

        void Init() override;

        void SetSprite(GL::Texture *texture);
        const GL::Texture *GetSprite() const;
    };

}