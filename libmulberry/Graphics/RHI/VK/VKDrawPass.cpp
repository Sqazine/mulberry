#include "VKDrawPass.h"
#include "VKContext.h"
#include "VKDevice.h"
#include "VKSwapChain.h"
#include "Math/MathUtils.h"
#include "App.h"
#include <array>
namespace mulberry
{
    VKDrawPass::VKDrawPass()
    {
        auto extent = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetSwapChain()->GetExtent();
        auto swapChainImageFormat = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetSwapChain()->GetSurfaceFormat().format;
        auto swapChainImageCount = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetSwapChain()->GetImageSize();

        mRenderPass = std::make_unique<VKRenderPass>(swapChainImageFormat);
        mCommandBuffers = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->GetGraphicsCommandPool()->CreatePrimaryCommandBuffers(swapChainImageCount);

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
    VKDrawPass::~VKDrawPass()
    {
    }

    void VKDrawPass::SetClearColor(const Color &clearColor)
    {
        mClearColor = clearColor;
    }

    void VKDrawPass::IsClearColorBuffer(bool isClear)
    {
        mIsClearColorBuffer = isClear;
    }

    void VKDrawPass::Begin()
    {
        mInFlightFences[mCurFrameIdx]->Wait();

        mSwapChainImageIdx = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetSwapChain()->AcquireNextImage(mImageAvailableSemaphores[mCurFrameIdx].get());

        mInFlightFences[mCurFrameIdx]->Reset();

        GetCurCommandBuffer()->Reset();

        GetCurCommandBuffer()->Begin();

        std::array<VkClearValue, 1> clearValues{};
        clearValues[0] = {{{mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a}}};

        VkRenderPassBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        beginInfo.pNext = nullptr;
        beginInfo.renderArea.offset = {0, 0};
        beginInfo.renderArea.extent.width = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetSwapChain()->GetExtent().x;
        beginInfo.renderArea.extent.height = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetSwapChain()->GetExtent().y;
        beginInfo.framebuffer = mFrameBuffers[mCurFrameIdx]->GetHandle();
        beginInfo.clearValueCount = clearValues.size();
        beginInfo.pClearValues = clearValues.data();
        beginInfo.renderPass = mRenderPass->GetHandle();

        GetCurCommandBuffer()->BeginRenderPass(beginInfo);
    }

    void VKDrawPass::End()
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

        App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->GetGraphicsQueue()->Submit(submitInfo, mInFlightFences[mCurFrameIdx].get());

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &App::GetInstance().GetGraphicsContext()->GetVKContext()->GetSwapChain()->GetHandle();
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &mRenderFinishedSemaphores[mCurFrameIdx]->GetHandle();
        presentInfo.pImageIndices = &mSwapChainImageIdx;

        App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->GetPresentQueue()->Present(presentInfo);

        mCurFrameIdx = (mCurFrameIdx + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    VKCommandBuffer *VKDrawPass::GetCurCommandBuffer()
    {
        return mCommandBuffers[mCurFrameIdx].get();
    }

    void VKDrawPass::ReBuild()
    {
        auto extent = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetSwapChain()->GetExtent();
        for (int32_t i = 0; i < mFrameBuffers.size(); ++i)
        {
            std::vector<const VKImageView *> views = {App::GetInstance().GetGraphicsContext()->GetVKContext()->GetSwapChain()->GetImageViews()[i].get()};
            mFrameBuffers[i] = std::make_unique<VKFrameBuffer>(extent.x, extent.y, mRenderPass.get(), views);
        }
    }
}