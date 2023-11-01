#include "VKRasterPipeline.h"
#include "VKContext.h"
#include "VKDevice.h"
#include "App.h"
namespace mulberry
{
    VKRasterPipeline::VKRasterPipeline()
        : mIsDirty(true),mHandle(VK_NULL_HANDLE)
    {
    }

    VKRasterPipeline::VKRasterPipeline(const RasterPipelineState &state)
        : mState(state), mIsDirty(true),mHandle(VK_NULL_HANDLE)
    {
    }

    VKRasterPipeline::~VKRasterPipeline()
    {
        if(mHandle)
            vkDestroyPipeline(App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->GetHandle(), mHandle, nullptr);
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