#include "VKSurface.h"
#include "VKUtils.h"
#include "VKContext.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include "App.h"
#include "Platform/Window.h"
#include "Logger.h"

namespace mulberry
{
	VKSurface::VKSurface(const VkInstance &instance)
		: mInstanceHandle(instance), mSurfaceHandle(VK_NULL_HANDLE)
	{
		if (SDL_Vulkan_CreateSurface(App::GetInstance().GetWindow()->GetHandle(), mInstanceHandle, &mSurfaceHandle) != SDL_TRUE)
			MULBERRY_CORE_ERROR("[ERROR]:failed to create vulkan surface.");
	}

	VKSurface::~VKSurface()
	{
		vkDestroySurfaceKHR(mInstanceHandle, mSurfaceHandle, nullptr);
	}

	const VkSurfaceKHR &VKSurface::GetHandle() const
	{
		return mSurfaceHandle;
	}
}