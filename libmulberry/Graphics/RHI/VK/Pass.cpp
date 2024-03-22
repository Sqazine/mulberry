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
    SwapChainPass::SwapChainPass()
        : mSwapChain(std::make_unique<SwapChain>()), mCurFrameIdx(0)
    {
        size_t size = mSwapChain->GetTextures().size();

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
    }

    void SwapChainPass::Begin()
    {
        if (App::GetInstance().GetWindow()->HasEvent(Window::Event::MAX | Window::Event::MIN | Window::Event::RESIZE))
        {
            mSwapChain->SyncToWindowSize();
            mCurFrameIdx = 0;
        }

        GetFence()->Wait();

        mSwapChain->AcquireNextImage(GetWaitSemaphore());

        auto frameBuffer = mSwapChain->GetDefaultFrameBuffer(GetCurFrameIdx());
        auto renderPass = mSwapChain->GetDefaultRenderPass();

        mFences[GetCurFrameIdx()]->Reset();

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

    void SwapChainPass::SetClearColor(const Color &clearColor)
    {
        mClearColor = clearColor;
    }

    void SwapChainPass::IsClearColorBuffer(bool isClear)
    {
        mIsClearColorBuffer = isClear;
    }

    void SwapChainPass::SetViewport(const Viewport &viewport)
    {
        auto [v, s] = ToVkViewPort(viewport);
        GetCommandBuffer()->SetViewport(v);
        GetCommandBuffer()->SetScissor(s);
    }

    void SwapChainPass::SetPipeline(GraphicsPipeline *pipeline)
    {
        auto renderPass = mSwapChain->GetDefaultRenderPass();
        pipeline->SetRenderPass(renderPass);
        GetCommandBuffer()->BindPipeline(pipeline);
    }

    Semaphore *SwapChainPass::GetWaitSemaphore() const
    {
        return mWaitSemaphores[GetCurFrameIdx()].get();
    }
    
    Semaphore *SwapChainPass::GetSignalSemaphore() const
    {
        return mSignalSemaphores[GetCurFrameIdx()].get();
    }

    void SwapChainPass::End()
    {
        GetCommandBuffer()->EndRenderPass();

        GetCommandBuffer()->End();

        GetCommandBuffer()->Submit({PipelineStage::COLOR_ATTACHMENT_OUTPUT}, {GetWaitSemaphore()}, {GetSignalSemaphore()}, {GetFence()});

        auto result = mSwapChain->Present(GetSignalSemaphore());

        mCurFrameIdx = (mCurFrameIdx + 1) % ((int32_t)mSwapChain->GetTextures().size());

        if (result != VK_SUCCESS)
        {
            mSwapChain->SyncToWindowSize();
            mCurFrameIdx = 0;
        }
    }

    GraphicsCommandBuffer *SwapChainPass::GetCommandBuffer() const
    {
        return mGraphicsCommandBuffers[GetCurFrameIdx()].get();
    }

    size_t SwapChainPass::GetCurFrameIdx() const
    {
        return mCurFrameIdx;
    }

    Fence *SwapChainPass::GetFence() const
    {
        return mFences[GetCurFrameIdx()].get();
    }
}