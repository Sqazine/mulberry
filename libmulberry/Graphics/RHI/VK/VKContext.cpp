#include "VKContext.h"
#include <iostream>
#include "VKDevice.h"
#include "VKSwapChain.h"
#include "Graphics/RHI/GraphicsContext.h"

namespace mulberry
{

	void VKContext::Init()
	{
		mAdapter = new VKAdapter();

#ifdef _DEBUG
		mAdapter->PrintInstanceInfo();
		mAdapter->PrintPhysicalDeviceSpecs();
#endif
		mDevice = mAdapter->CreateDevice();
		mSwapChain = new VKSwapChain();
	}

	void VKContext::Destroy()
	{
		delete mSwapChain;
		mSwapChain = nullptr;

		delete mDevice;
		mDevice = nullptr;

		delete mAdapter;
		mAdapter = nullptr;
	}

	VKAdapter *VKContext::GetAdapter() const
	{
		return mAdapter;
	}

	VKDevice *VKContext::GetDevice() const
	{
		return mDevice;
	}

	void VKContext::BeginFrame()
	{
	}
	void VKContext::EndFrame()
	{
	}
}