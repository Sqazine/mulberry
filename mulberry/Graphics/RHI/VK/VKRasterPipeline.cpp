#include "VKRasterPipeline.h"
#include "VKContext.h"
#include "VKDevice.h"
#include "App.h"
#include "Logger.h"
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
            vkDestroyPipeline(RAW_VK_DEVICE_HANDLE, mHandle, nullptr);
    }

    void VKRasterPipeline::SetPSO(const RasterPipelineState &state)
    {
        mState = state;
        mIsDirty=true;
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
        info.sType=VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        info.pNext=nullptr;
        info.flags=0;
        info.subpass = 0;

        
        VK_CHECK(vkCreateGraphicsPipelines(RAW_VK_DEVICE_HANDLE, VK_NULL_HANDLE, 1, &info, nullptr, &mHandle));
    }
}