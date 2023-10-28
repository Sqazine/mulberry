#pragma once
#include "Graphics/RHI/RasterPipeline.h"
namespace mulberry
{
    class VKRasterPipeline
    {
    public:
        VKRasterPipeline();
        VKRasterPipeline(const RasterPipelineConfig &config);
        ~VKRasterPipeline();

        void SetBufferClearColor(const Color &color);
        void ClearColorBuffer();

        Viewport GetViewport() const;
        void SetViewport(const Viewport &info);

        void SetPointSize(uint32_t size);
        uint32_t GetPointSize() const;

        void SetCull(CullType cullType);
        const CullType &GetCullType() const;

        void SetDepthTest(DepthTestType depthTest);
        const DepthTestType &GetDepthTest() const;

        void SetDepthMask(DepthMask depthMask);
        const DepthMask &GetDepthMask() const;

        void SetStencilMask(StencilMask stencilMask);
        const StencilMask &GetStencilMask() const;

        void SetBlendState(bool isOpen, BlendFunc srcFunc, BlendFunc dstFunc);
        std::tuple<bool, BlendFunc, BlendFunc> GetBlendState() const;

        void Render(const VKIndexBuffer *ibo, PrimitiveRenderType mode);
        void RenderInstanced(const VKIndexBuffer *ibo, PrimitiveRenderType mode, uint32_t instanceCount);

        const VkPipeline &GetHandle();

    private:
        void Build();
        RasterPipelineConfig mConfig;

        bool mIsDirty;

        VkPipeline mHandle;
    };
}