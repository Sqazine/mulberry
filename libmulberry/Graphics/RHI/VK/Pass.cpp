#include "Pass.h"
#include "Device.h"
#include "SwapChain.h"
#include "Math/MathUtils.h"
#include "Utils.h"
#include "App.h"
#include "GRaphicsContext.h"
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

    void Pass::SetClearColor(const Color &clearColor)
    {
        mClearColor = clearColor;
    }

    void Pass::IsClearColorBuffer(bool isClear)
    {
        mIsClearColorBuffer = isClear;
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

    size_t Pass::GetCurFrameIdx() const
    {
        return mCurFrameIdx;
    }

    SwapChainPass::SwapChainPass()
        : mSwapChain(std::make_unique<SwapChain>())
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

        mRenderPass = std::make_unique<RenderPass>(mSwapChain->GetSurfaceFormat().format);

        mFrameBuffers.resize(size);
        for (int32_t i = 0; i < mFrameBuffers.size(); ++i)
        {
            mFrameBuffers[i] = std::make_unique<FrameBuffer>();
            mFrameBuffers[i]->AttachRenderPass(mRenderPass.get()).AttachTexture(mSwapChain->GetTextures()[i]);
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
            mFrameBuffers.resize(mSwapChain->GetTextures().size());
            for (int32_t i = 0; i < mFrameBuffers.size(); ++i)
            {
                mFrameBuffers[i] = std::make_unique<FrameBuffer>();
                mFrameBuffers[i]->AttachRenderPass(mRenderPass.get()).AttachTexture(mSwapChain->GetTextures()[i]);
            }
            mCurFrameIdx = 0;
        }

        GetFence()->Wait();

        mSwapChain->AcquireNextImage(GetWaitSemaphore());

        auto frameBuffer = mFrameBuffers[GetCurFrameIdx()].get();

        mFences[GetCurFrameIdx()]->Reset();

        GetCommandBuffer()->Reset();

        GetCommandBuffer()->Begin();

        std::vector<VkClearValue> clearValues(1);
        clearValues[0] = {{{mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a}}};

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

        mCurFrameIdx = (mCurFrameIdx + 1) % ((int32_t)mSwapChain->GetTextures().size());

        if (result != VK_SUCCESS)
        {
            mSwapChain->SyncToWindowSize();
            mFrameBuffers.resize(mSwapChain->GetTextures().size());
            for (int32_t i = 0; i < mFrameBuffers.size(); ++i)
            {
                mFrameBuffers[i] = std::make_unique<FrameBuffer>();
                mFrameBuffers[i]->AttachRenderPass(mRenderPass.get()).AttachTexture(mSwapChain->GetTextures()[i]);
            }
            mCurFrameIdx = 0;
        }
    }
}