#include "Surface.h"
#include "Utils.h"
#include "Context.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include "App.h"
#include "Window.h"
#include "Logger.h"

namespace mulberry::vk
{
	Surface::Surface()
		: mSurfaceHandle(VK_NULL_HANDLE)
	{
		if (SDL_Vulkan_CreateSurface(App::GetInstance().GetWindow()->GetHandle(), Context::GetInstance().GetAdapter()->GetInstanceHandle(), &mSurfaceHandle) != SDL_TRUE)
		{
			MULBERRY_CORE_ERROR("[ERROR]:failed to create vulkan surface.");
			exit(1);
		}
	}
	Surface::~Surface()
	{
		vkDestroySurfaceKHR(Context::GetInstance().GetAdapter()->GetInstanceHandle(), mSurfaceHandle, nullptr);
	}

	const VkSurfaceKHR &Surface::GetHandle() const
	{
		return mSurfaceHandle;
	}
}