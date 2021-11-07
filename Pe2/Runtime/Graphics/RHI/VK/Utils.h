#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include <cassert>

namespace VK
{

#define VK_CHECK_RESULT(f)                                                                                  \
	{                                                                                                       \
		VkResult res = (f);                                                                                 \
		if (res != VK_SUCCESS)                                                                              \
		{                                                                                                   \
			std::cout << "Fatal : VkResult!=VK_SUCCESS in " << __FILE__ << " at line " << __LINE__ << "\n"; \
			assert(res == VK_SUCCESS);                                                                      \
		}                                                                                                   \
	}

	std::vector<const char *> GetSDLRequiredExtensions(SDL_Window *window);

}