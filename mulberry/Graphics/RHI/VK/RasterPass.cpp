#include "RasterPass.h"
#include "Device.h"
#include "SwapChain.h"
#include "Math/MathUtils.h"
#include "Utils.h"
#include "App.h"
#include "GRaphicsContext.h"
#include <array>
namespace mulberry::rhi::vk
{
    RasterPass::RasterPass(std::vector<Texture *> &textureLists)
    {
        mRenderPass = std::make_unique<RenderPass>(textureLists[0]->GetImage()->GetFormat());

        mFrameBuffers.resize(textureLists.size());

        ReBuild(textureLists);

        auto size = (int32_t)textureLists.size();

        mRasterCommandBuffers = mDevice.GetRasterCommandPool()->CreatePrimaryCommandBuffers(size);
       
        mWaitSemaphores.resize(size);
        mSignalSemaphores.resize(size);
        mInFlightFences.resize(size);

        for (size_t i = 0; i < size; ++i)
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
        return mWaitSemaphores[GetCurFrameIdx()].get();
    }
    Semaphore *RasterPass::GetSignalSemaphore() const
    {
        return mSignalSemaphores[GetCurFrameIdx()].get();
    }

    void RasterPass::Begin()
    {
        mInFlightFences[GetCurFrameIdx()]->Wait();
        mInFlightFences[GetCurFrameIdx()]->Reset();

        GetCommandBuffer()->Reset();

        GetCommandBuffer()->Begin();

        std::vector<VkClearValue> clearValues(1);
        clearValues[0] = {{{mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a}}};

        VkRect2D renderArea = {};
        renderArea.offset = {0, 0};
        renderArea.extent.width = (uint32_t)mFrameBuffers[GetCurFrameIdx()]->GetExtent().x;
        renderArea.extent.height = (uint32_t)mFrameBuffers[GetCurFrameIdx()]->GetExtent().y;

        GetCommandBuffer()->BeginRenderPass(mRenderPass->GetHandle(), mFrameBuffers[GetCurFrameIdx()]->GetHandle(), renderArea, clearValues, VK_SUBPASS_CONTENTS_INLINE);
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
        submitInfo.pWaitSemaphores = &GetWaitSemaphore()->GetHandle();
        submitInfo.pWaitDstStageMask = waitStageMasks;
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &GetSignalSemaphore()->GetHandle();

        VK_CONTEXT->GetDevice()->GetRasterQueue()->Submit(submitInfo, mInFlightFences[GetCurFrameIdx()].get());
    }

    RasterCommandBuffer *RasterPass::GetCommandBuffer() const
    {
        return mRasterCommandBuffers[GetCurFrameIdx()].get();
    }

    uint32_t RasterPass::GetCurFrameIdx() const
    {
        return VK_CONTEXT->GetCurFrameIdx();
    }

    void RasterPass::ReBuild(std::vector<Texture *> &textureLists)
    {
        for (int32_t i = 0; i < mFrameBuffers.size(); ++i)
            mFrameBuffers[i] = std::make_unique<FrameBuffer>(textureLists[i]->GetImage()->GetExtent().x, textureLists[i]->GetImage()->GetExtent().y, mRenderPass.get(), textureLists[i]);
    }
}