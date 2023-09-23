#pragma once
#include <string>
#include <string_view>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include "Vec2.h"
#include "Logger.h"
#include "Graphics/RHI/VK/VKAdapter.h"
#include "Graphics/RHI/RasterPipeline.h"

namespace mulberry
{
	class SDL2Window
	{
	public:
		SDL2Window();
		~SDL2Window();

		void SetTitle(std::string_view str);
		std::string_view GetTitle() const;
		void Resize(const Vec2 &extent);
		void Resize(uint32_t w, uint32_t h);
		Vec2 GetSize();
		SDL_Window *GetHandle();

		const Viewport &GetViewport() const;

		void Show();
		void Hide();

	private:
		SDL_Window *mHandle;
		std::string mTitle = "";

		Viewport mViewport;

		bool mIsShown;
	private:
		friend class Window;

		std::vector<const char *> GetVulkanRequiredExtensions();
		VkSurfaceKHR CreateSurface(VkInstance instance);
	};

}