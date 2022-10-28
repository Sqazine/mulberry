#pragma once
#include <memory>
#include "Graphics/GL/Shader.h"
#include "Graphics/GL/Texture.h"
namespace mulberry
{
    class RenderMaterial
    {
    public:
        RenderMaterial() {}
        virtual ~RenderMaterial() {}

        std::unique_ptr<GL::ShaderProgram> shaderProgram;
    };

    class SpriteMaterial : public RenderMaterial
    {
    public:
        SpriteMaterial();
        ~SpriteMaterial() override;

        void SetSpriteTexture(GL::Texture *sprite);

        GL::Texture *spriteTexture;
    };

    class GizmoMaterial : public RenderMaterial
    {
    public:
        GizmoMaterial();
        ~GizmoMaterial() override;
    };
}