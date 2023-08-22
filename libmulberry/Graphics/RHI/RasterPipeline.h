#pragma once
#include <cstdint>
#include "Math/Color.h"
#include "Graphics/Primitive.h"
namespace mulberry
{
    class GLRasterPipeline;

    enum class PrimitiveRenderType
    {
        POINT_LIST,
        LINE_LIST,
        LINE_STRIP,
        TRIANGLE_LIST,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };

    enum class CullType
    {
        NONE,
        FRONT,
        BACK,
        FRONT_AND_BACK
    };

    enum class DepthTestType
    {
        NONE,
        ALWAYS,
        NEVER,
        LESS,
        EQUAL,
        LESS_EQUAL,
        GREATER,
        NOT_EQUAL,
        GREATER_EQUAL,
    };

    enum class DepthMask
    {
        OPEN,
        CLOSE,
    };

    enum class StencilMask
    {
        OPEN,
        CLOSE,
    };

    enum class BlendFunc
    {
        ZERO,
        ONE,

        SRC_COLOR,
        ONE_MINUS_SRC_COLOR,

        DST_COLOR,
        ONE_MINUS_DST_COLOR,

        SRC_ALPHA,
        ONE_MINUS_SRC_ALPHA,

        DST_ALPHA,
        ONE_MINUS_DST_ALPHA,

        CONSTANT_COLOR,
        ONE_MINUS_CONSTANT_COLOR,

        CONSTANT_ALPHA,
        ONE_MINUS_CONSTANT_ALPHA,

        SRC_ALPHA_SATURATE,

        SRC1_COLOR,
        ONE_MINUS_SRC1_COLOR,

        SRC1_ALPHA,
        ONE_MINUS_SRC1_ALPHA
    };

    struct Viewport
    {
        uint32_t x, y, width, height;
    };

    struct RasterPipelineConfig
    {
        Viewport viewport;
        PrimitiveRenderType primitiveType;
        CullType cullType;
        DepthTestType depthTestType;
        DepthMask depthMask;
        StencilMask stencilMask;
        std::tuple<bool, BlendFunc, BlendFunc> blendState;
        Color clearColor;
        uint32_t pointSize;
    };

    class RasterPipeline
    {
    public:
        RasterPipeline();
        RasterPipeline(const RasterPipelineConfig &config);
        ~RasterPipeline();

        void SetBufferClearColor(const Color &color);
        void ClearColorBuffer();
        Viewport GetViewport();
        void SetViewport(const Viewport &info);
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        void SetPointSize(uint32_t size);
        uint32_t GetPointSize() const;

        void SetCull(CullType cullType);
        const CullType &GetCull() const;

        void SetDepthTest(DepthTestType depthTest);
        const DepthTestType &GetDepthTest() const;

        void SetDepthMask(DepthMask depthMask);
        const DepthMask &GetDepthMask() const;

        void SetStencilMask(StencilMask stencilMask);
        const StencilMask &GetStencilMask() const;

        void SetBlendState(bool isOpen, BlendFunc srcFunc=BlendFunc::SRC_ALPHA, BlendFunc dstFunc=BlendFunc::ONE_MINUS_SRC_ALPHA);
        std::tuple<bool, BlendFunc, BlendFunc> GetBlendState() const;

        void Render(const Primitive &primitive, PrimitiveRenderType mode);
        void RenderInstanced(const Primitive &primitive, PrimitiveRenderType mode, uint32_t instanceCount);

    private:
        std::unique_ptr<class GLRasterPipeline> mGLRasterPipeline;
        std::unique_ptr<class VKRasterPipeline> mVKRasterPipeline;
    };
}