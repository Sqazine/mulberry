#pragma once

namespace mulberry::rhi::vk
{
    class Base
    {
    public:
        Base();
        ~Base();

        class Device& GetDevice();
    protected:
        class Device &mDevice;
    };
}