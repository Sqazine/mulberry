#pragma once
#include <vector>
#include <vulkan/vulkan.h>

#include "Image.h"
namespace VK
{
	class SwapChain 
	{
	public:
		SwapChain();
		~SwapChain();
	private:
		VkSurfaceFormatKHR ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		VkPresentModeKHR ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		VkExtent2D ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		VkSwapchainKHR m_SwapChainHandle;

		std::vector<VkImage> m_SwapChainImages;
		std::vector<VkImageView> m_SwapChainImageViews;
		VkSurfaceFormatKHR m_SwapChainSurfaceFormat;
		VkExtent2D m_SwapChainImageExtent;
		VkPresentModeKHR m_SwapChainPresentMode;
	};
}