#pragma once
#include <vulkan/vulkan.h>
namespace mulberry
{
    constexpr uint64_t FENCE_WAIT_TIME_OUT = UINT64_MAX;

    enum class FenceStatus
    {
        SIGNALED,
        UNSIGNALED,
    };

    class VKFence
    {
    public:
        VKFence(FenceStatus status);
        ~VKFence();

        const VkFence &GetHandle() const;

        void Wait(bool waitAll = true, uint64_t timeout = FENCE_WAIT_TIME_OUT);
        void Reset();

        FenceStatus GetStatus() const;
    private:
        VkFence mHandle;
        FenceStatus mStatus;
    };

    class VKSemaphore
    {
    public:
        VKSemaphore();
        ~VKSemaphore();

        const VkSemaphore &GetHandle() const;
    private:
        VkSemaphore mHandle;
    };
}