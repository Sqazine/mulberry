#pragma once

namespace mulberry::vk
{
    class Base
    {
    public:
        Base();
        ~Base();

        class Device &GetDevice();

    protected:
        virtual void Build() {}

        bool mIsDirty;

        class Device &mDevice;
    };
}