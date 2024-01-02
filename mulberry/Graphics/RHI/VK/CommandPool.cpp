#include "CommandPool.h"
#include "Context.h"
#include "Device.h"
#include "Utils.h"
#include "App.h"
namespace mulberry::vk
{
#define COMMAND_POOL_DEF(name, queueIdx)                              \
    name##CommandPool::name##CommandPool() : CommandPool<name##CommandBuffer>(queueIdx) {} \
    name##CommandPool::~name##CommandPool() {}

	COMMAND_POOL_DEF(Raster, VK_CONTEXT->GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.graphicsFamilyIdx.value())
	COMMAND_POOL_DEF(Compute, VK_CONTEXT->GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.computeFamilyIdx.value())
	COMMAND_POOL_DEF(Transfer, VK_CONTEXT->GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.transferFamilyIdx.value())
}