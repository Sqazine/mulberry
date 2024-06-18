#include "GraphicsContext.h"
#include <iostream>
#include "Device.h"
#include "SwapChain.h"
#include "Command.h"
#include "Pass.h"
#include "App.h"
#include "Graphics/RHI/Pass.h"
namespace mulberry::vk
{
	GraphicsContext::GraphicsContext()
	{
	}
	GraphicsContext::~GraphicsContext()
	{
	}

	void GraphicsContext::Init()
	{
		mAdapter = std::make_unique<Adapter>();

#ifdef _DEBUG
		mAdapter->PrintInstanceInfo();
		mAdapter->PrintPhysicalDeviceSpecs();
#endif
		mDevice.reset(mAdapter->CreateDevice());
	}

	Adapter *GraphicsContext::GetAdapter() const
	{
		return mAdapter.get();
	}

	Device *GraphicsContext::GetDevice() const
	{
		return mDevice.get();
	}
}