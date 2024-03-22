#pragma once
#include <vector>
#include <memory>
#include <vulkan/vulkan.h>
#include "Base.h"
#include "Command.h"
#include "FrameBuffer.h"
#include "Color.h"
#include "Math/Vec2.h"
#include "Enum.h"
#include "Format.h"
#include "Texture.h"
namespace mulberry::rhi::vk
{
    class SwapChainPass : public Base
    {
    public:
        SwapChainPass();
        virtual ~SwapChainPass();

        Fence *GetFence() const;
        
        virtual void Begin();

        void SetClearColor(const Color &clearColor);
        void IsClearColorBuffer(bool isClear);

        void SetViewport(const Viewport &viewport);
        void SetPipeline(GraphicsPipeline *pipeline);

        virtual void End();

    protected:
        Semaphore *GetWaitSemaphore() const;
        Semaphore *GetSignalSemaphore() const;
        GraphicsCommandBuffer *GetCommandBuffer() const;

        size_t GetCurFrameIdx() const;

    private:

        friend class GraphicsContext;

        std::unique_ptr<class SwapChain> mSwapChain;

        std::vector<std::unique_ptr<GraphicsCommandBuffer>> mGraphicsCommandBuffers;

        std::vector<std::unique_ptr<Semaphore>> mWaitSemaphores;
        std::vector<std::unique_ptr<Semaphore>> mSignalSemaphores;
        std::vector<std::unique_ptr<Fence>> mFences;

        Color mClearColor;
        bool mIsClearColorBuffer;

        size_t mCurFrameIdx = 0;

    };
}
