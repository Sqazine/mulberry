#include "Object.h"
#include "App.h"
#include "Device.h"
#include "GraphicsContext.h"
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

    Device &Object::GetDevice()
    {
        return mDevice;
    }
}