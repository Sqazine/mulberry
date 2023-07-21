#include "Context.h"
#include <iostream>
#include "Device.h"
#include "Surface.h"
#include "SwapChain.h"
#include "Graphics/GraphicsContext.h"

namespace mulberry::vk
{

	void Context::Init()
	{
		mAdapter = new Adapter();
		mDevice = mAdapter->CreateDevice();
		mSwapChain = new SwapChain();
	}

	void Context::Destroy()
	{
		delete mSwapChain;
		mSwapChain = nullptr;

		delete mDevice;
		mDevice = nullptr;

		delete mAdapter;
		mAdapter = nullptr;
	}

	Adapter *Context::GetAdapter() const
	{
		return mAdapter;
	}

	Device *Context::GetDevice() const
	{
		return mDevice;
	}

	void Context::BeginFrame()
	{
	}
	void Context::EndFrame()
	{
	}
}