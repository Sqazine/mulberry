#include "VKSwapChain.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include "VKContext.h"
#include "VKDevice.h"
#include "VKUtils.h"
#include "Logger.h"
#include "App.h"
namespace mulberry
{

	VKSwapChain::VKSwapChain()
		: mHandle(VK_NULL_HANDLE), mNextImageIdx(0)
	{
		Build();
	}

	VKSwapChain::~VKSwapChain()
	{
		DeleteImageViews();

		vkDestroySwapchainKHR(RAW_VK_DEVICE_HANDLE, mHandle, nullptr);
	}

	const std::vector<std::vector<VKImageView *>> &VKSwapChain::GetImageViews() const
	{
		return mSwapChainImageViews;
	}

	const VkSurfaceFormatKHR VKSwapChain::GetSurfaceFormat() const
	{
		return mSwapChainSurfaceFormat;
	}

	Vec2 VKSwapChain::GetExtent() const
	{
		return Vec2(mSwapChainImageExtent.width, mSwapChainImageExtent.height);
	}

	void VKSwapChain::AcquireNextImage(const VKSemaphore *semaphore, const VKFence *fence)
	{

		if (semaphore && fence)
			VK_CHECK(vkAcquireNextImageKHR(RAW_VK_DEVICE_HANDLE, mHandle, UINT64_MAX, semaphore->GetHandle(), fence->GetHandle(), &mNextImageIdx))
		else if (semaphore && !fence)
			VK_CHECK(vkAcquireNextImageKHR(RAW_VK_DEVICE_HANDLE, mHandle, UINT64_MAX, semaphore->GetHandle(), nullptr, &mNextImageIdx))
		else if (!semaphore && fence)
			VK_CHECK(vkAcquireNextImageKHR(RAW_VK_DEVICE_HANDLE, mHandle, UINT64_MAX, nullptr, fence->GetHandle(), &mNextImageIdx))
		else
			VK_CHECK(vkAcquireNextImageKHR(RAW_VK_DEVICE_HANDLE, mHandle, UINT64_MAX, nullptr, nullptr, &mNextImageIdx))
	}

	uint32_t VKSwapChain::GetNextImageIdx() const
	{
		return mNextImageIdx;
	}

	void VKSwapChain::Present(const VKSemaphore *waitSemaphore)
	{
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &VK_CONTEXT->GetSwapChain()->GetHandle();
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &waitSemaphore->GetHandle();
		presentInfo.pImageIndices = &mNextImageIdx;

		VK_CONTEXT->GetDevice()->GetPresentQueue()->Present(presentInfo);
	}

	void VKSwapChain::Build()
	{
		SwapChainDetails swapChainDetail = QuerySwapChainDetails();
		mSwapChainSurfaceFormat = ChooseSwapChainSurfaceFormat(swapChainDetail.surfaceFormats);
		mSwapChainPresentMode = ChooseSwapChainPresentMode(swapChainDetail.presentModes);
		mSwapChainImageExtent = ChooseSwapChainExtent(swapChainDetail.surfaceCapabilities);

		VkSwapchainCreateInfoKHR createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.surface = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetAdapter()->GetSurface();
		createInfo.minImageCount = uint32_t(App::GetInstance().GetGraphicsConfig().useDoubleBuffer ? 2 : 1);
		createInfo.imageFormat = mSwapChainSurfaceFormat.format;
		createInfo.imageColorSpace = mSwapChainSurfaceFormat.colorSpace;
		createInfo.imageExtent = mSwapChainImageExtent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = VK_CONTEXT->GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices;
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
		createInfo.oldSwapchain = mHandle == VK_NULL_HANDLE ? mHandle : VK_NULL_HANDLE;

		VK_CHECK(vkCreateSwapchainKHR(RAW_VK_DEVICE_HANDLE, &createInfo, nullptr, &mHandle));

		uint32_t count = 0;

		vkGetSwapchainImagesKHR(RAW_VK_DEVICE_HANDLE, mHandle, &count, nullptr);
		mSwapChainImages.resize(count);
		vkGetSwapchainImagesKHR(RAW_VK_DEVICE_HANDLE, mHandle, &count, mSwapChainImages.data());

		mSwapChainImageViews.resize(count);
		for (size_t i = 0; i < mSwapChainImageViews.size(); ++i)
			mSwapChainImageViews[i] = {new VKImageView(mSwapChainImages[i], mSwapChainSurfaceFormat.format, VK_IMAGE_VIEW_TYPE_2D, ImageAspect::COLOR)};
	}

	const VkSwapchainKHR &VKSwapChain::GetHandle() const
	{
		return mHandle;
	}

	void VKSwapChain::ReBuild()
	{
		VK_CONTEXT->GetDevice()->WaitIdle();

		DeleteImageViews();

		vkDestroySwapchainKHR(RAW_VK_DEVICE_HANDLE, mHandle, nullptr);
		Build();
	}

	VkSurfaceFormatKHR VKSwapChain::ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
	{
		for (const auto &availableFormat : availableFormats)
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return availableFormat;
		return availableFormats[0];
	}

	VkPresentModeKHR VKSwapChain::ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
	{
		for (const auto &availablePresentMode : availablePresentModes)
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				return availablePresentMode;

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VKSwapChain::ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR &capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max() && capabilities.currentExtent.height != std::numeric_limits<uint32_t>::max())
			return capabilities.currentExtent;
		else
		{
			auto size = App::GetInstance().GetWindow()->GetSize();
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

			void VKSwapChain::DeleteImageViews()
			{
				for (size_t i = 0; i < mSwapChainImageViews.size(); ++i)
			for (size_t j = 0; j < mSwapChainImageViews[i].size(); ++j)
			{
				delete mSwapChainImageViews[i][j];
				mSwapChainImageViews[i][j] = nullptr;
			}

		std::vector<std::vector<VKImageView *>>().swap(mSwapChainImageViews);
			}

	SwapChainDetails VKSwapChain::QuerySwapChainDetails()
	{
		SwapChainDetails result;

		auto surface = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetAdapter()->GetSurface();
		auto physicalDevice = VK_CONTEXT->GetDevice()->GetPhysicalDeviceSpec().handle;

		uint32_t count = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, nullptr);
		result.surfaceFormats.resize(count);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, result.surfaceFormats.data());

		count = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, nullptr);
		result.presentModes.resize(count);
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, result.presentModes.data());

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &result.surfaceCapabilities);

		return result;
	}
}