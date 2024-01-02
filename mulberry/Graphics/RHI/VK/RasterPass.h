#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "CommandBuffer.h"
#include "CommandPool.h"
#include "RenderPass.h"
#include "FrameBuffer.h"
#include "Math/Color.h"
#include "Math/Vec2.h"
#include "Enum.h"
#include "Format.h"
#include "Texture.h"
namespace mulberry::vk
{
    class RasterPass:public Object
    {
    public:
        RasterPass(const Vec2 &extent, Format format, std::vector<Texture *> &textureLists);
        virtual ~RasterPass();

        void SetClearColor(const Color &clearColor);
        void IsClearColorBuffer(bool isClear);

        virtual void Begin();
        virtual void End();
    protected:
        friend class Context;

        Semaphore *GetWaitSemaphore() const;
        Semaphore *GetSignalSemaphore() const;
        RasterCommandBuffer *GetCommandBuffer() const;

    private:
        void ReBuild(const Vec2 &extent, std::vector<Texture *> &textureLists);

        Vec2 mExtent;

        std::unique_ptr<RenderPass> mRenderPass;
        std::vector<std::unique_ptr<FrameBuffer>> mFrameBuffers;

        std::vector<std::unique_ptr<RasterCommandBuffer>> mRasterCommandBuffers;

        std::vector<std::unique_ptr<Semaphore>> mWaitSemaphores;
        std::vector<std::unique_ptr<Semaphore>> mSignalSemaphores;
        std::vector<std::unique_ptr<Fence>> mInFlightFences;

        Color mClearColor;
        bool mIsClearColorBuffer;
    };
}
