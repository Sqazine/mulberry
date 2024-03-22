#pragma once
#include <memory>
#include "Math/Vec2.h"
#include "Graphics/RHI/Shader.h"
#include "Graphics/RHI/Texture.h"
#include "Graphics/RHI/Pipeline.h"
namespace mulberry
{
    class GraphicsMaterial
    {
    public:
        GraphicsMaterial() : mGraphicsPipeline(std::make_unique<rhi::GraphicsPipeline>()) {}
        virtual ~GraphicsMaterial() {}

        virtual void SetDefaultUniformValue() const {}

        rhi::GraphicsPipeline *GetGraphicsPipeline()
        {
            return mGraphicsPipeline.get();
        }

        const rhi::GraphicsPipeline *GetGraphicsPipeline() const
        {
            return mGraphicsPipeline.get();
        }

    protected:
        std::unique_ptr<rhi::GraphicsPipeline> mGraphicsPipeline;
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

    class SpriteMaterial : public GraphicsMaterial
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

    class GizmoMaterial : public GraphicsMaterial
    {
    public:
        GizmoMaterial();
        ~GizmoMaterial() override;
    };
}