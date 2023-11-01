#pragma once
#include <vector>
#include <memory>
#include "VKCommand.h"
#include "VKRenderPass.h"
#include "VKFrameBuffer.h"
#include "Math/Color.h"
namespace mulberry
{
#define MAX_FRAMES_IN_FLIGHT 2

    class VKDrawPass
    {
    public:
        VKDrawPass();
        ~VKDrawPass();

        void SetClearColor(const Color &clearColor);
        void IsClearColorBuffer(bool isClear);

        void Begin();
        void End();

    protected:
        friend class VKContext;
        void ReBuild();
        VKCommandBuffer *GetCurCommandBuffer();

        uint32_t mSwapChainImageIdx;

        std::unique_ptr<VKRenderPass> mRenderPass;
        std::vector<std::unique_ptr<VKFrameBuffer>> mFrameBuffers;

        std::vector<std::unique_ptr<VKCommandBuffer>> mCommandBuffers;

        std::vector<std::unique_ptr<VKSemaphore>> mImageAvailableSemaphores;
        std::vector<std::unique_ptr<VKSemaphore>> mRenderFinishedSemaphores;
        std::vector<std::unique_ptr<VKFence>> mInFlightFences;

        size_t mCurFrameIdx = 0;

        Color mClearColor;
        bool mIsClearColorBuffer;
    };
}
