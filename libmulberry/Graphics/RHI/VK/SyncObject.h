#pragma once
#include <vulkan/vulkan.h>
#include "Base.h"
namespace mulberry::vk
{
    constexpr uint64_t FENCE_WAIT_TIME_OUT = UINT64_MAX;

    enum class FenceStatus
    {
        SIGNALED,
        UNSIGNALED,
    };

    class Fence :public Base
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

    class Semaphore :public Base
    {
    public:
        Semaphore();
        ~Semaphore();

        const VkSemaphore &GetHandle() const;
    private:
        VkSemaphore mHandle;
    };
}