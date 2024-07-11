#pragma once
#include <vector>
#include <memory>
#include <vulkan/vulkan.h>
#include "Defs.h"
#include "Command.h"
#include "FrameBuffer.h"
#include "Color.h"
#include "Math/Vec2.h"
#include "Format.h"
#include "Texture.h"
namespace mulberry::vk
{
    class Pass : public Base
    {
    public:
        Pass();
        virtual ~Pass();

        virtual void Begin();

        void SetViewport(const Viewport &viewport);
        void SetPipeline(GraphicsPipeline *pipeline);

        virtual void End();

    protected:
        Semaphore *GetWaitSemaphore() const;
        Semaphore *GetSignalSemaphore() const;

        Fence *GetFence() const;

        GraphicsCommandBuffer *GetCommandBuffer() const;
        FrameBuffer* GetFrameBuffer() const;

        size_t GetCurFrameIdx() const;

        std::unique_ptr<class RenderPass> mRenderPass;
        std::vector<std::unique_ptr<class FrameBuffer>> mFrameBuffers;

        std::vector<std::unique_ptr<GraphicsCommandBuffer>> mGraphicsCommandBuffers;

        std::vector<std::unique_ptr<Semaphore>> mWaitSemaphores;
        std::vector<std::unique_ptr<Semaphore>> mSignalSemaphores;
        std::vector<std::unique_ptr<Fence>> mFences;

        size_t mCurFrameIdx = 0;
    };
    class SwapChainPass : public Pass
    {
    public:
        SwapChainPass();
        ~SwapChainPass() override;

        void Begin() override;

        void End() override;

        mulberry::ColorAttachment* GetColorAttachment() const;
    private:
        void SyncToWindowSize();
        void BuildFrameBuffer();
        friend class GraphicsContext;

        std::unique_ptr<class SwapChain> mSwapChain;
    };
}
