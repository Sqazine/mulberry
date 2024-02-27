#pragma once

namespace mulberry::rhi::vk
{
    class Object
    {
    public:
        Object();
        ~Object();

        class Device& GetDevice();
    protected:
        class Device &mDevice;
    };
}