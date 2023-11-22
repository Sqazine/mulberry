#include "VKRasterPass.h"
#include "VKContext.h"
#include "VKDevice.h"
#include "VKSwapChain.h"
#include "Math/MathUtils.h"
#include "VKUtils.h"
#include "App.h"
#include <array>
#include "Graphics/RHI/Texture.h"
namespace mulberry
{
    VKRasterPass::VKRasterPass(const Vec2 &extent, Format format, const std::vector<std::vector<const VKTexture *>> &textureLists)
        : VKRasterPass(extent, ToVkFormat(format), textureLists)
    {
    }

    VKRasterPass::VKRasterPass(const Vec2 &extent, VkFormat format, const std::vector<std::vector<const VKTexture *>> &textureLists)
    {
        mRenderPass = std::make_unique<VKRenderPass>(format);
        mCommandBuffers = VK_CONTEXT->GetDevice()->GetGraphicsCommandPool()->CreatePrimaryCommandBuffers(textureLists.size());

        mFrameBuffers.resize(textureLists.size());

        ReBuild(extent, textureLists);

        mWaitSemaphores.resize(textureLists.size());
        mSignalSemaphores.resize(textureLists.size());
        mInFlightFences.resize(textureLists.size());

        for (size_t i = 0; i < textureLists.size(); ++i)
        {
            mWaitSemaphores[i] = std::make_unique<VKSemaphore>();
            mSignalSemaphores[i] = std::make_unique<VKSemaphore>();
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

    VKSemaphore *VKRasterPass::GetWaitSemaphore() const
    {
        return mWaitSemaphores[VK_CONTEXT->GetCurFrameIdx()].get();
    }
    VKSemaphore *VKRasterPass::GetSignalSemaphore() const
    {
        return mSignalSemaphores[VK_CONTEXT->GetCurFrameIdx()].get();
    }

    void VKRasterPass::Begin()
    {
        VK_CONTEXT->mCurRasterPass = this;

        mInFlightFences[VK_CONTEXT->GetCurFrameIdx()]->Wait();
        mInFlightFences[VK_CONTEXT->GetCurFrameIdx()]->Reset();

        GetCommandBuffer()->Reset();

        GetCommandBuffer()->Begin();

        std::array<VkClearValue, 1> clearValues{};
        clearValues[0] = {{{mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a}}};

        VkRenderPassBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        beginInfo.pNext = nullptr;
        beginInfo.renderArea.offset = {0, 0};
        beginInfo.renderArea.extent.width = (uint32_t)mExtent.x;
        beginInfo.renderArea.extent.height = (uint32_t)mExtent.y;
        beginInfo.framebuffer = mFrameBuffers[VK_CONTEXT->GetCurFrameIdx()]->GetHandle();
        beginInfo.clearValueCount = clearValues.size();
        beginInfo.pClearValues = clearValues.data();
        beginInfo.renderPass = mRenderPass->GetHandle();

        GetCommandBuffer()->BeginRenderPass(beginInfo);
    }

    void VKRasterPass::End()
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

        VK_CONTEXT->GetDevice()->GetGraphicsQueue()->Submit(submitInfo, mInFlightFences[VK_CONTEXT->GetCurFrameIdx()].get());

        VK_CONTEXT->mCurRasterPass = nullptr;
    }

    VKCommandBuffer *VKRasterPass::GetCommandBuffer() const
    {
        return mCommandBuffers[VK_CONTEXT->GetCurFrameIdx()].get();
    }

    void VKRasterPass::ReBuild(const Vec2 &extent, const std::vector<std::vector<const VKTexture *>> &textureLists)
    {
        mExtent = extent;
        for (int32_t i = 0; i < mFrameBuffers.size(); ++i)
            mFrameBuffers[i] = std::make_unique<VKFrameBuffer>(extent.x, extent.y, mRenderPass.get(), textureLists[i]);
    }
}