#include "SwapChain.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include "Context.h"
#include "Device.h"
#include "Surface.h"
#include "Utils.h"
namespace VK
{

	SwapChain::SwapChain()
		:  m_SwapChainHandle(VK_NULL_HANDLE)
	{

		SwapChainDetails swapChainDetail = Context::m_PhysicalDeviceList->GetSuitablePhysicalDevice().m_SwapChainDetails;
		m_SwapChainSurfaceFormat = ChooseSwapChainSurfaceFormat(swapChainDetail.surfaceFormats);
		m_SwapChainPresentMode = ChooseSwapChainPresentMode(swapChainDetail.presentModes);
		m_SwapChainImageExtent = ChooseSwapChainExtent(swapChainDetail.surfaceCapabilities);

		if (swapChainDetail.surfaceCapabilities.maxImageCount > 0 && Context::m_RenderCreateInfo.swapChainBufferCount > swapChainDetail.surfaceCapabilities.maxImageCount)
			Context::m_RenderCreateInfo.swapChainBufferCount = swapChainDetail.surfaceCapabilities.maxImageCount;

		VkSwapchainCreateInfoKHR createInfo{
			.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
			.pNext = nullptr,
			.flags = 0,
			.surface = Context::m_Surface->m_SurfaceHandle,
			.minImageCount = Context::m_RenderCreateInfo.swapChainBufferCount,
			.imageFormat = m_SwapChainSurfaceFormat.format,
			.imageColorSpace = m_SwapChainSurfaceFormat.colorSpace,
			.imageExtent = m_SwapChainImageExtent,
			.imageArrayLayers = 1,
			.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		};

		QueueFamilyIndices indices = Context::m_PhysicalDeviceList->GetSuitablePhysicalDevice().m_QueueFamilyIndices;
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(),indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainDetail.surfaceCapabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = m_SwapChainPresentMode;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		VK_CHECK_RESULT(vkCreateSwapchainKHR(Context::m_LogicalDevice->m_LogicalDeviceHandle, &createInfo, nullptr, &m_SwapChainHandle));

		vkGetSwapchainImagesKHR(Context::m_LogicalDevice->m_LogicalDeviceHandle, m_SwapChainHandle, &(Context::m_RenderCreateInfo.swapChainBufferCount), nullptr);
		m_SwapChainImages.resize(Context::m_RenderCreateInfo.swapChainBufferCount);
		vkGetSwapchainImagesKHR(Context::m_LogicalDevice->m_LogicalDeviceHandle, m_SwapChainHandle, &(Context::m_RenderCreateInfo.swapChainBufferCount), m_SwapChainImages.data());

		m_SwapChainImageViews.resize(Context::m_RenderCreateInfo.swapChainBufferCount);
		for (size_t i = 0; i < m_SwapChainImageViews.size(); ++i)
		{
			VkImageViewCreateInfo imageViewCreateInfo = {};
			imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			imageViewCreateInfo.pNext = nullptr;
			imageViewCreateInfo.flags = 0;
			imageViewCreateInfo.image = m_SwapChainImages[i];
			imageViewCreateInfo.format = m_SwapChainSurfaceFormat.format;
			imageViewCreateInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY };
			imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
			imageViewCreateInfo.subresourceRange.levelCount = 1;
			imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
			imageViewCreateInfo.subresourceRange.layerCount = 1;

			VK_CHECK_RESULT(vkCreateImageView(Context::m_LogicalDevice->m_LogicalDeviceHandle, &imageViewCreateInfo, nullptr, &m_SwapChainImageViews[i]));
		}

	}
	SwapChain::~SwapChain()
	{
		for (auto imageView : m_SwapChainImageViews)
			vkDestroyImageView(Context::m_LogicalDevice->m_LogicalDeviceHandle, imageView, nullptr);
		vkDestroySwapchainKHR(Context::m_LogicalDevice->m_LogicalDeviceHandle, m_SwapChainHandle, nullptr);
	}

	VkSurfaceFormatKHR SwapChain::ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats)
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return availableFormat;
		return availableFormats[0];
	}

	VkPresentModeKHR SwapChain::ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes)
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				return availablePresentMode;

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D SwapChain::ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max() && capabilities.currentExtent.height != std::numeric_limits<uint32_t>::max())
			return capabilities.currentExtent;
		else
		{
			int32_t width, height;
			SDL_GetWindowSize(Context::m_WindowHandle, &width, &height);
			VkExtent2D actualExtent =
			{
				(uint32_t)width,
				(uint32_t)height,
			};

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}
}