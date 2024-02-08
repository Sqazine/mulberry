#include "Object.h"
#include "App.h"
#include "Device.h"
#include "Context.h"
#include "Utils.h"

namespace mulberry::rhi::vk
{
    Object::Object()
        : mDevice(*VK_DEVICE)
    {
    }

    Object::~Object()
    {
    }

    Device &Object::GetRelatedDevice()
    {
        return mDevice;
    }
}