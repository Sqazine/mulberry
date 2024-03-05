#include "Pass.h"
#include "Device.h"
#include "SwapChain.h"
#include "Math/MathUtils.h"
#include "Utils.h"
#include "App.h"
#include "GRaphicsContext.h"
#include <array>
namespace mulberry::rhi::vk
{
    GraphicsPass::GraphicsPass()
    {
        size_t size = VK_CONTEXT->GetSwapChain()->GetTextures().size();

        mGraphicsCommandBuffers = mDevice.GetGraphicsCommandPool()->CreatePrimaryCommandBuffers(size);

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

    GraphicsPass::~GraphicsPass()
    {
    }

    void GraphicsPass::Begin()
    {
        auto frameBuffer = VK_CONTEXT->GetSwapChain()->GetCurrentDefaultFrameBuffer();
        auto renderPass = VK_CONTEXT->GetSwapChain()->GetDefaultRenderPass();

        mInFlightFences[GetCurFrameIdx()]->Wait();
        mInFlightFences[GetCurFrameIdx()]->Reset();

        GetCommandBuffer()->Reset();

        GetCommandBuffer()->Begin();

        std::vector<VkClearValue> clearValues(1);
        clearValues[0] = {{{mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a}}};

        VkRect2D renderArea = {};
        renderArea.offset = {0, 0};
        renderArea.extent.width = (uint32_t)frameBuffer->GetExtent().x;
        renderArea.extent.height = (uint32_t)frameBuffer->GetExtent().y;

        GetCommandBuffer()->BeginRenderPass(renderPass->GetHandle(), frameBuffer->GetHandle(), renderArea, clearValues, VK_SUBPASS_CONTENTS_INLINE);
    }

    void GraphicsPass::SetClearColor(const Color &clearColor)
    {
        mClearColor = clearColor;
    }

    void GraphicsPass::IsClearColorBuffer(bool isClear)
    {
        mIsClearColorBuffer = isClear;
    }

    void GraphicsPass::SetViewport(const Viewport &viewport)
    {
        auto [v, s] = ToVkViewPort(viewport);
        GetCommandBuffer()->SetViewport(v);
        GetCommandBuffer()->SetScissor(s);
    }

    void GraphicsPass::SetPipeline(GraphicsPipeline *pipeline)
    {
        auto renderPass = VK_CONTEXT->GetSwapChain()->GetDefaultRenderPass();
        pipeline->SetRenderPass(renderPass);
        GetCommandBuffer()->BindPipeline(pipeline);
    }

    Semaphore *GraphicsPass::GetWaitSemaphore() const
    {
        return mWaitSemaphores[GetCurFrameIdx()].get();
    }
    Semaphore *GraphicsPass::GetSignalSemaphore() const
    {
        return mSignalSemaphores[GetCurFrameIdx()].get();
    }

    void GraphicsPass::End()
    {
        GetCommandBuffer()->EndRenderPass();

        GetCommandBuffer()->End();

        GetCommandBuffer()->Submit({PipelineStage::COLOR_ATTACHMENT_OUTPUT}, {GetWaitSemaphore()}, {GetSignalSemaphore()}, {GetFence()});
    }

    GraphicsCommandBuffer *GraphicsPass::GetCommandBuffer() const
    {
        return mGraphicsCommandBuffers[GetCurFrameIdx()].get();
    }

    size_t GraphicsPass::GetCurFrameIdx() const
    {
        return VK_CONTEXT->GetCurFrameIdx();
    }

    Fence *GraphicsPass::GetFence() const
    {
        return mInFlightFences[GetCurFrameIdx()].get();
    }
}