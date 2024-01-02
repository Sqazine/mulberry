#include "RasterPass.h"
#include "Device.h"
#include "SwapChain.h"
#include "Math/MathUtils.h"
#include "Utils.h"
#include "App.h"
#include "Context.h"
#include <array>
namespace mulberry::vk
{
    RasterPass::RasterPass(const Vec2 &extent, Format format,std::vector<Texture *> &textureLists)
    {
        mRenderPass = std::make_unique<RenderPass>(format);
        mRasterCommandBuffers = mDevice.GetRasterCommandPool()->CreatePrimaryCommandBuffers(textureLists.size());

        mFrameBuffers.resize(textureLists.size());

        ReBuild(extent, textureLists);

        mWaitSemaphores.resize(textureLists.size());
        mSignalSemaphores.resize(textureLists.size());
        mInFlightFences.resize(textureLists.size());

        for (size_t i = 0; i < textureLists.size(); ++i)
        {
            mWaitSemaphores[i] = std::make_unique<Semaphore>();
            mSignalSemaphores[i] = std::make_unique<Semaphore>();
            mInFlightFences[i] = std::make_unique<Fence>(FenceStatus::SIGNALED);
        }
    }

    RasterPass::~RasterPass()
    {
    }

    void RasterPass::SetClearColor(const Color &clearColor)
    {
        mClearColor = clearColor;
    }

    void RasterPass::IsClearColorBuffer(bool isClear)
    {
        mIsClearColorBuffer = isClear;
    }

    Semaphore *RasterPass::GetWaitSemaphore() const
    {
        return mWaitSemaphores[VK_CONTEXT->GetCurFrameIdx()].get();
    }
    Semaphore *RasterPass::GetSignalSemaphore() const
    {
        return mSignalSemaphores[VK_CONTEXT->GetCurFrameIdx()].get();
    }

    void RasterPass::Begin()
    {
        VK_CONTEXT->mCurRasterPass = this;

        mInFlightFences[VK_CONTEXT->GetCurFrameIdx()]->Wait();
        mInFlightFences[VK_CONTEXT->GetCurFrameIdx()]->Reset();

        GetCommandBuffer()->Reset();

        GetCommandBuffer()->Begin();

        std::vector<VkClearValue> clearValues(1);
        clearValues[0] = {{{mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a}}};

        VkRect2D renderArea = {};
        renderArea.offset = {0, 0};
        renderArea.extent.width = (uint32_t)mExtent.x;
        renderArea.extent.height = (uint32_t)mExtent.y;

        GetCommandBuffer()->BeginRenderPass(mRenderPass->GetHandle(), mFrameBuffers[VK_CONTEXT->GetCurFrameIdx()]->GetHandle(), renderArea, clearValues, VK_SUBPASS_CONTENTS_INLINE);
    }

    void RasterPass::End()
    {
        GetCommandBuffer()->EndRenderPass();

        GetCommandBuffer()->End();

        VkPipelineStageFlags waitStageMasks[] = {
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &GetCommandBuffer()->GetHandle();
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &mWaitSemaphores[VK_CONTEXT->GetCurFrameIdx()]->GetHandle();
        submitInfo.pWaitDstStageMask = waitStageMasks;
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &mSignalSemaphores[VK_CONTEXT->GetCurFrameIdx()]->GetHandle();

        VK_CONTEXT->GetDevice()->GetRasterQueue()->Submit(submitInfo, mInFlightFences[VK_CONTEXT->GetCurFrameIdx()].get());

        VK_CONTEXT->mCurRasterPass = nullptr;
    }

    RasterCommandBuffer *RasterPass::GetCommandBuffer() const
    {
        return mRasterCommandBuffers[VK_CONTEXT->GetCurFrameIdx()].get();
    }

    void RasterPass::ReBuild(const Vec2 &extent, std::vector<Texture *> &textureLists)
    {
        mExtent = extent;
        for (int32_t i = 0; i < mFrameBuffers.size(); ++i)
            mFrameBuffers[i] = std::make_unique<FrameBuffer>(extent.x, extent.y, mRenderPass.get(), textureLists[i]);
    }
}