#pragma once
#include <cstdint>
#include "Math/Color.h"
#include "Graphics/Primitive.h"
#include "RasterPipelineState.h"
namespace mulberry
{
    class GLRasterPipeline;

    class RasterPipeline
    {
    public:
        RasterPipeline();
        RasterPipeline(const RasterPipelineState &state);
        ~RasterPipeline();

        void SetPSO(const RasterPipelineState &state);
        const RasterPipelineState &GetPSO() const;
        RasterPipelineState &GetPSO();

        void Render(const Primitive &primitive);
        void RenderInstanced(const Primitive &primitive, uint32_t instanceCount);

    private:
        std::unique_ptr<class GLRasterPipeline> mGLRasterPipeline;
        std::unique_ptr<class VKRasterPipeline> mVKRasterPipeline;
    };
}