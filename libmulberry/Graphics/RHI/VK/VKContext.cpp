#include "VKContext.h"
#include <iostream>
#include "VKDevice.h"
#include "VKSwapChain.h"
#include "VKCommand.h"
#include "Graphics/RHI/GraphicsContext.h"
#include "App.h"
#include "VKDrawPass.h"
namespace mulberry
{
	VKContext::VKContext()
	{
	}
	VKContext::~VKContext()
	{
	}

	void VKContext::Init()
	{
		mAdapter = std::make_unique<VKAdapter>();

#ifdef _DEBUG
		mAdapter->PrintInstanceInfo();
		mAdapter->PrintPhysicalDeviceSpecs();
#endif
		mDevice.reset(mAdapter->CreateDevice());
		mSwapChain = std::make_unique<VKSwapChain>();

		mDefaultDrawPass = std::make_unique<VKDrawPass>();
	}

	VKAdapter *VKContext::GetAdapter() const
	{
		return mAdapter.get();
	}

	VKDevice *VKContext::GetDevice() const
	{
		return mDevice.get();
	}

	VKSwapChain *VKContext::GetSwapChain() const
	{
		return mSwapChain.get();
	}

	void VKContext::SetClearColor(const Color &clearColor)
	{
		mDefaultDrawPass->SetClearColor(clearColor);
	}
	void VKContext::IsClearColorBuffer(bool isClear)
	{
		mDefaultDrawPass->IsClearColorBuffer(isClear);
	}

	void VKContext::BeginFrame()
	{
		if (App::GetInstance().GetWindow()->IsResize())
		{
			mSwapChain->ReBuild();
			mDefaultDrawPass->ReBuild();
		}

		mDefaultDrawPass->Begin();
	}
	void VKContext::EndFrame()
	{
		mDefaultDrawPass->End();
	}
}