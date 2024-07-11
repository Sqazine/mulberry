#include "Pass.h"
#include "Device.h"
#include "SwapChain.h"
#include "Math/MathUtils.h"
#include "Utils.h"
#include "App.h"
#include "GraphicsContext.h"
#include "Attachment.h"
#include <array>
namespace mulberry::vk
{
    Pass::Pass()
        : mCurFrameIdx(0)
    {
    }

    Pass::~Pass()
    {
    }

    void Pass::Begin()
    {
    }

    void Pass::SetViewport(const Viewport &viewport)
    {
        auto [v, s] = ToVkViewPort(viewport);
        GetCommandBuffer()->SetViewport(v);
        GetCommandBuffer()->SetScissor(s);
    }

    void Pass::SetPipeline(GraphicsPipeline *pipeline)
    {
        pipeline->SetRenderPass(mRenderPass.get());
        GetCommandBuffer()->BindPipeline(pipeline);
    }

    void Pass::End()
    {
    }

    Semaphore *Pass::GetWaitSemaphore() const
    {
        return mWaitSemaphores[GetCurFrameIdx()].get();
    }

    Semaphore *Pass::GetSignalSemaphore() const
    {
        return mSignalSemaphores[GetCurFrameIdx()].get();
    }

    Fence *Pass::GetFence() const
    {
        return mFences[GetCurFrameIdx()].get();
    }

    GraphicsCommandBuffer *Pass::GetCommandBuffer() const
    {
        return mGraphicsCommandBuffers[GetCurFrameIdx()].get();
    }

    FrameBuffer *Pass::GetFrameBuffer() const
    {
        return mFrameBuffers[GetCurFrameIdx()].get();
    }

    size_t Pass::GetCurFrameIdx() const
    {
        return mCurFrameIdx;
    }

    SwapChainPass::SwapChainPass()
        : mSwapChain(std::make_unique<SwapChain>())
    {
        size_t size = mSwapChain->GetAttachmentCount();

        mRenderPass = std::make_unique<RenderPass>(ToFormat(mSwapChain->GetSurfaceFormat().format));

        BuildFrameBuffer();
        for (int32_t i = 0; i < mFrameBuffers.size(); ++i)
        {
            mFrameBuffers[i] = std::make_unique<FrameBuffer>();
            mFrameBuffers[i]->AttachRenderPass(mRenderPass.get()).BindColorAttachment(0, mSwapChain->GetAttachmentByIndex(i));
        }

        mGraphicsCommandBuffers = mDevice.GetGraphicsCommandPool()->CreatePrimaryCommandBuffers(size);

        mWaitSemaphores.resize(size);
        mSignalSemaphores.resize(size);
        mFences.resize(size);

        for (size_t i = 0; i < size; ++i)
        {
            mWaitSemaphores[i] = std::make_unique<Semaphore>();
            mSignalSemaphores[i] = std::make_unique<Semaphore>();
            mFences[i] = std::make_unique<Fence>(FenceStatus::SIGNALED);
        }
    }

    SwapChainPass::~SwapChainPass()
    {
        mDevice.GetGraphicsQueue()->WaitIdle();
    }

    void SwapChainPass::Begin()
    {
        if (App::GetInstance().GetWindow()->HasEvent(Window::Event::MAX | Window::Event::MIN | Window::Event::RESIZE))
            SyncToWindowSize();

        GetFence()->Wait();

        mSwapChain->AcquireNextImage(GetWaitSemaphore());

        GetFence()->Reset();

        GetCommandBuffer()->Reset();

        GetCommandBuffer()->Begin();

        auto frameBuffer = GetFrameBuffer();

        std::vector<VkClearValue> clearValues(1);
        for (auto &[k, v] : frameBuffer->GetColorAttachments())
            clearValues[0] = (dynamic_cast<vk::ColorAttachment *>(v))->GetVkClearValue();
        VkRect2D renderArea = {};
        renderArea.offset = {0, 0};
        renderArea.extent.width = (uint32_t)frameBuffer->GetExtent().x;
        renderArea.extent.height = (uint32_t)frameBuffer->GetExtent().y;

        GetCommandBuffer()->BeginRenderPass(mRenderPass->GetHandle(), frameBuffer->GetHandle(), renderArea, clearValues, VK_SUBPASS_CONTENTS_INLINE);
    }

    void SwapChainPass::End()
    {
        GetCommandBuffer()->EndRenderPass();

        GetCommandBuffer()->End();

        GetCommandBuffer()->Submit({PipelineStage::COLOR_ATTACHMENT_OUTPUT}, {GetWaitSemaphore()}, {GetSignalSemaphore()}, {GetFence()});

        auto result = mSwapChain->Present(GetSignalSemaphore());

        mCurFrameIdx = (mCurFrameIdx + 1) % ((int32_t)mSwapChain->GetAttachmentCount());

        if (result != VK_SUCCESS)
            SyncToWindowSize();
    }

    mulberry::ColorAttachment *SwapChainPass::GetColorAttachment() const
    {
        return GetFrameBuffer()->GetColorAttachment(0);
    }

    void SwapChainPass::SyncToWindowSize()
    {
        mSwapChain->SyncToWindowSize();
        BuildFrameBuffer();
        mCurFrameIdx = 0;
    }

    void SwapChainPass::BuildFrameBuffer()
    {
        mFrameBuffers.resize(mSwapChain->GetAttachmentCount());
        for (int32_t i = 0; i < mFrameBuffers.size(); ++i)
        {
            mFrameBuffers[i] = std::make_unique<FrameBuffer>();
            mFrameBuffers[i]->AttachRenderPass(mRenderPass.get()).BindColorAttachment(0, mSwapChain->GetAttachmentByIndex(i));
        }
    }

}