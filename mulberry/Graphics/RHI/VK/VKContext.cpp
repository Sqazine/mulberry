#include "VKContext.h"
#include <iostream>
#include "VKDevice.h"
#include "VKSwapChain.h"
#include "VKCommand.h"
#include "Graphics/RHI/GraphicsContext.h"
#include "App.h"
#include "VKRasterPass.h"
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

		mDefaultRasterPass = std::make_unique<VKRasterPass>();
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
		mDefaultRasterPass->SetClearColor(clearColor);
	}
	void VKContext::IsClearColorBuffer(bool isClear)
	{
		mDefaultRasterPass->IsClearColorBuffer(isClear);
	}

	void VKContext::BeginFrame()
	{
		if (App::GetInstance().GetWindow()->IsResize())
		{
			mSwapChain->ReBuild();
			mDefaultRasterPass->ReBuild();
		}

		mDefaultRasterPass->Begin();
	}
	void VKContext::EndFrame()
	{
		mDefaultRasterPass->End();
	}

	const VKRasterPass *VKContext::GetCurRasterPass() const
	{
		return mCurRasterPass;
	}
}