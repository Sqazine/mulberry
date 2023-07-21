#include "SwapChain.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include "Context.h"
#include "Device.h"
#include "Surface.h"
#include "Utils.h"
#include "Logger.h"
#include "App.h"
namespace mulberry::vk
{

	SwapChain::SwapChain()
		: mSwapChainHandle(VK_NULL_HANDLE)
	{

		SwapChainDetails swapChainDetail = Context::GetInstance().GetDevice()->GetPhysicalDeviceSpec().swapChainDetails;
		mSwapChainSurfaceFormat = ChooseSwapChainSurfaceFormat(swapChainDetail.surfaceFormats);
		mSwapChainPresentMode = ChooseSwapChainPresentMode(swapChainDetail.presentModes);
		mSwapChainImageExtent = ChooseSwapChainExtent(swapChainDetail.surfaceCapabilities);

		VkSwapchainCreateInfoKHR createInfo{
			.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
			.pNext = nullptr,
			.flags = 0,
			.surface = Context::GetInstance().GetAdapter()->GetSurface()->GetHandle(),
			.minImageCount = uint32_t(App::GetInstance().GetGraphicsConfig().useDoubleBuffer ? 2 : 1),
			.imageFormat = mSwapChainSurfaceFormat.format,
			.imageColorSpace = mSwapChainSurfaceFormat.colorSpace,
			.imageExtent = mSwapChainImageExtent,
			.imageArrayLayers = 1,
			.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		};

		QueueFamilyIndices indices = Context::GetInstance().GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices;
		uint32_t queueFamilyIndices[] = {indices.graphicsFamilyIdx.value(), indices.presentFamilyIdx.value()};

		if (indices.graphicsFamilyIdx.value() != indices.presentFamilyIdx.value())
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
		createInfo.presentMode = mSwapChainPresentMode;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		VK_CHECK(vkCreateSwapchainKHR(Context::GetInstance().GetDevice()->GetHandle(), &createInfo, nullptr, &mSwapChainHandle));

		uint32_t count=0;

		vkGetSwapchainImagesKHR(Context::GetInstance().GetDevice()->GetHandle(), mSwapChainHandle, &count, nullptr);
		mSwapChainImages.resize(count);
		vkGetSwapchainImagesKHR(Context::GetInstance().GetDevice()->GetHandle(), mSwapChainHandle, &count, mSwapChainImages.data());

		mSwapChainImageViews.resize(count);
		for (size_t i = 0; i < mSwapChainImageViews.size(); ++i)
		{
			VkImageViewCreateInfo imageViewCreateInfo = {};
			imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			imageViewCreateInfo.pNext = nullptr;
			imageViewCreateInfo.flags = 0;
			imageViewCreateInfo.image = mSwapChainImages[i];
			imageViewCreateInfo.format = mSwapChainSurfaceFormat.format;
			imageViewCreateInfo.components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY};
			imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
			imageViewCreateInfo.subresourceRange.levelCount = 1;
			imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
			imageViewCreateInfo.subresourceRange.layerCount = 1;

			VK_CHECK(vkCreateImageView(Context::GetInstance().GetDevice()->GetHandle(), &imageViewCreateInfo, nullptr, &mSwapChainImageViews[i]));
		}
	}
	SwapChain::~SwapChain()
	{
		for (auto imageView : mSwapChainImageViews)
			vkDestroyImageView(Context::GetInstance().GetDevice()->GetHandle(), imageView, nullptr);
		vkDestroySwapchainKHR(Context::GetInstance().GetDevice()->GetHandle(), mSwapChainHandle, nullptr);
	}

	VkSurfaceFormatKHR SwapChain::ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
	{
		for (const auto &availableFormat : availableFormats)
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return availableFormat;
		return availableFormats[0];
	}

	VkPresentModeKHR SwapChain::ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
	{
		for (const auto &availablePresentMode : availablePresentModes)
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				return availablePresentMode;

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D SwapChain::ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR &capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max() && capabilities.currentExtent.height != std::numeric_limits<uint32_t>::max())
			return capabilities.currentExtent;
		else
		{
			auto size=App::GetInstance().GetWindow()->GetSize();
			VkExtent2D actualExtent =
				{
					(uint32_t)size.x,
					(uint32_t)size.y,
				};

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}
}