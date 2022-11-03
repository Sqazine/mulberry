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

        virtual void SetUniformValue() const {}

        std::unique_ptr<GL::ShaderProgram> shaderProgram;
    };

    class SpriteMaterial : public RenderMaterial
    {
    public:
        SpriteMaterial();
        ~SpriteMaterial() override;

        void SetSprite(GL::Texture *sprite);
        const GL::Texture *GetSprite() const;

        void SetTiling(const Vec2 &t);
        const Vec2 &GetTiling() const;

        void SetOffSet(const Vec2& o);
        const Vec2& GetOffset() const;

        void SetUniformValue() const override;

    private:
        GL::Texture *mSprite;
        Vec2 mTiling;
        Vec2 mOffset;
    };

    class GizmoMaterial : public RenderMaterial
    {
    public:
        GizmoMaterial();
        ~GizmoMaterial() override;
    };
}