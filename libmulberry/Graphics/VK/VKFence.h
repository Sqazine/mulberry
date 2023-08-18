#pragma once
#include <vulkan/vulkan.h>

namespace mulberry
{
    class VKFence
    {
    public:
        VKFence();
        ~VKFence();

        const VkFence &GetHandle() const;

        void Wait();
        void Reset();

    private:
        VkFence mHandle;
    };
}