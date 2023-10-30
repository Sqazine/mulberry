#pragma once
#include "Graphics/RHI/RasterPipeline.h"
namespace mulberry
{
    class VKRasterPipeline
    {
    public:
        VKRasterPipeline();
        VKRasterPipeline(const RasterPipelineState &state);
        ~VKRasterPipeline();

        void SetPSO(const RasterPipelineState &state);
        const RasterPipelineState &GetPSO() const;
        RasterPipelineState &GetPSO();

        void Render(const VKIndexBuffer *ibo);
        void RenderInstanced(const VKIndexBuffer *ibo, uint32_t instanceCount);

        const VkPipeline &GetHandle();

    private:
        void Build();
        RasterPipelineState mState;

        bool mIsDirty;

        VkPipeline mHandle;
    };
}