#pragma once
#include <memory>
#include "Math/Vec2.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
namespace mulberry
{
    class RenderMaterial
    {
    public:
        RenderMaterial() {}
        virtual ~RenderMaterial() {}

        virtual void SetUniformValue() const {}
        virtual void ResetUniformValue() const {}

        void SetShaderProgram(ShaderProgram *program);
        ShaderProgram *GetShaderProgram() const;

    protected:
        std::unique_ptr<ShaderProgram> shaderProgram;
    };

    class SpriteMaterial : public RenderMaterial
    {
    public:
        SpriteMaterial();
        ~SpriteMaterial() override;

        void SetSprite(Texture *sprite);
        const Texture *GetSprite() const;

        void SetTiling(const Vec2 &t);
        const Vec2 &GetTiling() const;

        void SetOffSet(const Vec2 &o);
        const Vec2 &GetOffset() const;

        void SetUniformValue() const override;
        void ResetUniformValue() const override;

    private:
        Texture *mSprite;
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