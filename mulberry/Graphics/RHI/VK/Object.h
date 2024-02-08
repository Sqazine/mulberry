#pragma once

namespace mulberry::rhi::vk
{
    class Object
    {
    public:
        Object();
        ~Object();

        class Device& GetRelatedDevice();
    protected:
        class Device &mDevice;
    };
}