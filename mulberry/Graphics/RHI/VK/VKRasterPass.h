#pragma once
#include <vector>
#include <memory>
#include "VKCommand.h"
#include "VKRenderPass.h"
#include "VKFrameBuffer.h"
#include "Math/Color.h"
#include "Math/Vec2.h"
namespace mulberry
{
    class VKRasterPass
    {
    public:
        VKRasterPass(const Vec2 &extent, enum class Format format, const std::vector<std::vector<VKImageView *>> &viewLists);
        VKRasterPass(const Vec2 &extent, VkFormat format, const std::vector<std::vector<VKImageView *>> &viewLists);
        ~VKRasterPass();

        void SetClearColor(const Color &clearColor);
        void IsClearColorBuffer(bool isClear);

        virtual void Begin();
        virtual void End();

    protected:
        friend class VKContext;

        VKSemaphore *GetWaitSemaphore() const;
        VKSemaphore *GetSignalSemaphore() const;
        VKCommandBuffer *GetCommandBuffer() const;

    private:
        void ReBuild(const Vec2 &extent, const std::vector<std::vector<VKImageView *>> &viewLists);

        Vec2 mExtent;

        std::unique_ptr<VKRenderPass> mRenderPass;
        std::vector<std::unique_ptr<VKFrameBuffer>> mFrameBuffers;

        std::vector<std::unique_ptr<VKCommandBuffer>> mCommandBuffers;

        std::vector<std::unique_ptr<VKSemaphore>> mWaitSemaphores;
        std::vector<std::unique_ptr<VKSemaphore>> mSignalSemaphores;
        std::vector<std::unique_ptr<VKFence>> mInFlightFences;

        Color mClearColor;
        bool mIsClearColorBuffer;
    };
}
