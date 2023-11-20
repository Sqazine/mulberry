#include "VKRasterPass.h"
#include "VKContext.h"
#include "VKDevice.h"
#include "VKSwapChain.h"
#include "Math/MathUtils.h"
#include "App.h"
#include <array>
namespace mulberry
{
    VKRasterPass::VKRasterPass()
    {
        auto extent = VK_CONTEXT->GetSwapChain()->GetExtent();
        auto swapChainImageFormat = VK_CONTEXT->GetSwapChain()->GetSurfaceFormat().format;
        auto swapChainImageCount = VK_CONTEXT->GetSwapChain()->GetImageSize();

        mRenderPass = std::make_unique<VKRenderPass>(swapChainImageFormat);
        mCommandBuffers = VK_CONTEXT->GetDevice()->GetGraphicsCommandPool()->CreatePrimaryCommandBuffers(swapChainImageCount);

        mFrameBuffers.resize(swapChainImageCount);

        ReBuild();

        mImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        mRenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        mInFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
        {
            mImageAvailableSemaphores[i] = std::make_unique<VKSemaphore>();
            mRenderFinishedSemaphores[i] = std::make_unique<VKSemaphore>();
            mInFlightFences[i] = std::make_unique<VKFence>(FenceStatus::SIGNALED);
        }
    }
    VKRasterPass::~VKRasterPass()
    {
    }

    void VKRasterPass::SetClearColor(const Color &clearColor)
    {
        mClearColor = clearColor;
    }

    void VKRasterPass::IsClearColorBuffer(bool isClear)
    {
        mIsClearColorBuffer = isClear;
    }

    void VKRasterPass::Begin()
    {
        VK_CONTEXT->mCurRasterPass = this;

        mInFlightFences[mCurFrameIdx]->Wait();

        mSwapChainImageIdx = VK_CONTEXT->GetSwapChain()->AcquireNextImage(mImageAvailableSemaphores[mCurFrameIdx].get());

        mInFlightFences[mCurFrameIdx]->Reset();

        GetCurCommandBuffer()->Reset();

        GetCurCommandBuffer()->Begin();

        std::array<VkClearValue, 1> clearValues{};
        clearValues[0] = {{{mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a}}};

        VkRenderPassBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        beginInfo.pNext = nullptr;
        beginInfo.renderArea.offset = {0, 0};
        beginInfo.renderArea.extent.width = VK_CONTEXT->GetSwapChain()->GetExtent().x;
        beginInfo.renderArea.extent.height = VK_CONTEXT->GetSwapChain()->GetExtent().y;
        beginInfo.framebuffer = mFrameBuffers[mCurFrameIdx]->GetHandle();
        beginInfo.clearValueCount = clearValues.size();
        beginInfo.pClearValues = clearValues.data();
        beginInfo.renderPass = mRenderPass->GetHandle();

        GetCurCommandBuffer()->BeginRenderPass(beginInfo);
    }

    void VKRasterPass::End()
    {
        GetCurCommandBuffer()->EndRenderPass();

        GetCurCommandBuffer()->End();

        VkPipelineStageFlags waitStageMasks[] = {
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &GetCurCommandBuffer()->GetHandle();
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &mImageAvailableSemaphores[mCurFrameIdx]->GetHandle();
        submitInfo.pWaitDstStageMask = waitStageMasks;
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &mRenderFinishedSemaphores[mCurFrameIdx]->GetHandle();

        VK_CONTEXT->GetDevice()->GetGraphicsQueue()->Submit(submitInfo, mInFlightFences[mCurFrameIdx].get());

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &VK_CONTEXT->GetSwapChain()->GetHandle();
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &mRenderFinishedSemaphores[mCurFrameIdx]->GetHandle();
        presentInfo.pImageIndices = &mSwapChainImageIdx;

        VK_CONTEXT->GetDevice()->GetPresentQueue()->Present(presentInfo);

        mCurFrameIdx = (mCurFrameIdx + 1) % MAX_FRAMES_IN_FLIGHT;

        VK_CONTEXT->mCurRasterPass = this;
    }

    VKCommandBuffer *VKRasterPass::GetCurCommandBuffer() const
    {
        return mCommandBuffers[mCurFrameIdx].get();
    }

    void VKRasterPass::ReBuild()
    {
        auto extent = VK_CONTEXT->GetSwapChain()->GetExtent();
        for (int32_t i = 0; i < mFrameBuffers.size(); ++i)
        {
            std::vector<const VKImageView *> views = {VK_CONTEXT->GetSwapChain()->GetImageViews()[i].get()};
            mFrameBuffers[i] = std::make_unique<VKFrameBuffer>(extent.x, extent.y, mRenderPass.get(), views);
        }
    }
}