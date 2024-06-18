#include "Defs.h"
#include "App.h"
#include "Device.h"
#include "GraphicsContext.h"
#include "Utils.h"

namespace mulberry::vk
{
    Base::Base()
        : mDevice(*VK_DEVICE), mIsDirty(true)
    {
    }

    Base::~Base()
    {
    }

    Device &Base::GetDevice()
    {
        return mDevice;
    }
}