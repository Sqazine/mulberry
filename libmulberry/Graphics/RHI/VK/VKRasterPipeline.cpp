#include "VKRasterPipeline.h"
#include "VKContext.h"
#include "VKDevice.h"
namespace mulberry
{
    VKRasterPipeline::VKRasterPipeline()
        : mIsDirty(true)
    {
    }

    VKRasterPipeline::VKRasterPipeline(const RasterPipelineState &state)
        : mState(state), mIsDirty(true)
    {
    }

    VKRasterPipeline::~VKRasterPipeline()
    {
        vkDestroyPipeline(VKContext::GetInstance().GetDevice()->GetHandle(), mHandle, nullptr);
    }

    void VKRasterPipeline::SetPSO(const RasterPipelineState &state)
    {
        mState = state;
    }

    const RasterPipelineState &VKRasterPipeline::GetPSO() const
    {
        return mState;
    }

    RasterPipelineState &VKRasterPipeline::GetPSO()
    {
        return mState;
    }

    void VKRasterPipeline::Render(const VKIndexBuffer *ibo)
    {
    }

    void VKRasterPipeline::RenderInstanced(const VKIndexBuffer *ibo, uint32_t instanceCount)
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