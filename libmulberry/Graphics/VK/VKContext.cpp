#include "VKContext.h"
#include <iostream>
#include "VKDevice.h"
#include "VKSurface.h"
#include "VKSwapChain.h"
#include "Graphics/GraphicsContext.h"

namespace mulberry
{

	void VKContext::Init()
	{
		mAdapter = new VKAdapter();
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