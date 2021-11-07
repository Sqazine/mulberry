#include "Surface.h"
#include "Utils.h"
#include "Context.h"
#include "Instance.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

namespace VK
{

	Surface::Surface()
		: m_SurfaceHandle(VK_NULL_HANDLE)
	{
		if (SDL_Vulkan_CreateSurface(Context::m_WindowHandle, Context::m_Instance.get()->m_InstanceHandle, &m_SurfaceHandle) != SDL_TRUE)
		{
			SDL_Log("[ERROR]:failed to create vulkan surface.");
			exit(1);
		}
	}
	Surface::~Surface()
	{
		vkDestroySurfaceKHR(Context::m_Instance.get()->m_InstanceHandle, m_SurfaceHandle, nullptr);
	}
}