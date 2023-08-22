#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include "VKImage.h"
namespace mulberry
{
	class VKSwapChain 
	{
	public:
		VKSwapChain();
		~VKSwapChain();
	private:
		VkSurfaceFormatKHR ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		VkPresentModeKHR ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		VkExtent2D ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		VkSwapchainKHR mSwapChainHandle;

		std::vector<VkImage> mSwapChainImages;
		std::vector<VkImageView> mSwapChainImageViews;
		VkSurfaceFormatKHR mSwapChainSurfaceFormat;
		VkExtent2D mSwapChainImageExtent;
		VkPresentModeKHR mSwapChainPresentMode;
	};
}