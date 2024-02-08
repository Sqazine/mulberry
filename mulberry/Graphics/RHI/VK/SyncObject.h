#pragma once
#include <vulkan/vulkan.h>
#include "Object.h"
namespace mulberry::rhi::vk
{
    constexpr uint64_t FENCE_WAIT_TIME_OUT = UINT64_MAX;

    enum class FenceStatus
    {
        SIGNALED,
        UNSIGNALED,
    };

    class Fence :public Object
    {
    public:
        Fence(FenceStatus status=FenceStatus::UNSIGNALED);
        ~Fence();

        const VkFence &GetHandle() const;

        void Wait(bool waitAll = true, uint64_t timeout = FENCE_WAIT_TIME_OUT);
        void Reset();

        FenceStatus GetStatus() const;
    private:

        VkFence mHandle;
        FenceStatus mStatus;
    };

    class Semaphore :public Object
    {
    public:
        Semaphore();
        ~Semaphore();

        const VkSemaphore &GetHandle() const;
    private:
        VkSemaphore mHandle;
    };
}