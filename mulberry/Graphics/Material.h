#pragma once
#include <memory>
#include "Math/Vec2.h"
#include "Graphics/RHI/Shader.h"
#include "Graphics/RHI/Texture.h"
#include "Graphics/RHI/Pipeline.h"
namespace mulberry
{
    class RasterMaterial
    {
    public:
        RasterMaterial() {}
        virtual ~RasterMaterial() {}

        virtual void SetDefaultUniformValue() const {}

    protected:
        std::unique_ptr<rhi::RasterPipeline> mRasterPipeline;
    };

    class ComputeMaterial
    {
    public:
        ComputeMaterial() {}
        virtual ~ComputeMaterial() {}

        virtual void SetDefaultUniformValue() const {}

    protected:
        std::unique_ptr<rhi::ComputePipeline> mComputePipeline;
    };

    class SpriteMaterial : public RasterMaterial
    {
    public:
        SpriteMaterial();
        ~SpriteMaterial() override;

        void SetSprite(rhi::Texture *sprite);
        const rhi::Texture *GetSprite() const;

        void SetTiling(const Vec2 &t);
        const Vec2 &GetTiling() const;

        void SetOffSet(const Vec2 &o);
        const Vec2 &GetOffset() const;

        void SetDefaultUniformValue() const override;

    private:
        rhi::Texture *mSprite;
        Vec2 mTiling;
        Vec2 mOffset;
    };

    class GizmoMaterial : public RasterMaterial
    {
    public:
        GizmoMaterial();
        ~GizmoMaterial() override;
    };
}