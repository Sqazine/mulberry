#include "VKRasterPipeline.h"
#include "VKContext.h"
#include "VKDevice.h"
namespace mulberry
{
    VKRasterPipeline::VKRasterPipeline()
        : mIsDirty(true)
    {
    }

    VKRasterPipeline::VKRasterPipeline(const RasterPipelineConfig &config)
        : mConfig(config), mIsDirty(true)
    {
    }

    VKRasterPipeline::~VKRasterPipeline()
    {
        vkDestroyPipeline(VKContext::GetInstance().GetDevice()->GetHandle(), mHandle, nullptr);
    }

    void VKRasterPipeline::SetBufferClearColor(const Color &color)
    {
        mConfig.clearColor = color;
    }

    void VKRasterPipeline::ClearColorBuffer()
    {
    }

    Viewport VKRasterPipeline::GetViewport() const
    {
        return mConfig.viewport;
    }

    void VKRasterPipeline::SetViewport(const Viewport &info)
    {
        mConfig.viewport = info;
    }

    void VKRasterPipeline::SetPointSize(uint32_t size)
    {
        mConfig.pointSize = size;
    }
    uint32_t VKRasterPipeline::GetPointSize() const
    {
        return mConfig.pointSize;
    }

    void VKRasterPipeline::SetCull(CullType cullType)
    {
        mConfig.cullType = cullType;
    }
    const CullType &VKRasterPipeline::GetCullType() const
    {
        return mConfig.cullType;
    }

    void VKRasterPipeline::SetDepthTest(DepthTestType depthTest)
    {
        mConfig.depthTestType = depthTest;
    }
    const DepthTestType &VKRasterPipeline::GetDepthTest() const
    {
        return mConfig.depthTestType;
    }

    void VKRasterPipeline::SetDepthMask(DepthMask depthMask)
    {
        mConfig.depthMask = depthMask;
    }
    const DepthMask &VKRasterPipeline::GetDepthMask() const
    {
        return mConfig.depthMask;
    }

    void VKRasterPipeline::SetStencilMask(StencilMask stencilMask)
    {
        mConfig.stencilMask = stencilMask;
    }
    const StencilMask &VKRasterPipeline::GetStencilMask() const
    {
        return mConfig.stencilMask;
    }

    void VKRasterPipeline::SetBlendState(bool isOpen, BlendFunc srcFunc, BlendFunc dstFunc)
    {
        mConfig.blendState = {isOpen, srcFunc, dstFunc};
    }
    std::tuple<bool, BlendFunc, BlendFunc> VKRasterPipeline::GetBlendState() const
    {
        return mConfig.blendState;
    }

    void VKRasterPipeline::Render(const VKIndexBuffer *ibo, PrimitiveRenderType mode)
    {
    }
    void VKRasterPipeline::RenderInstanced(const VKIndexBuffer *ibo, PrimitiveRenderType mode, uint32_t instanceCount)
    {
    }

    const VkPipeline &VKRasterPipeline::GetHandle()
    {
        if (mHandle == VK_NULL_HANDLE || mIsDirty)
            Build();
        return mHandle;
    }

    void VKRasterPipeline::Build()
    {
        VkGraphicsPipelineCreateInfo info{};
    }
}