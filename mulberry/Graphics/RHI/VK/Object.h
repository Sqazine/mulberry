#pragma once

namespace mulberry::vk
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