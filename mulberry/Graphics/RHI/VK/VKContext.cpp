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

		mDefaultRasterPass = std::make_unique<VKRasterPass>(mSwapChain->GetExtent(),
															mSwapChain->GetSurfaceFormat().format,
															mSwapChain->GetTextures());
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
			mDefaultRasterPass->ReBuild(mSwapChain->GetExtent(), mSwapChain->GetTextures());
		}

		VK_CONTEXT->GetSwapChain()->AcquireNextImage(mDefaultRasterPass->GetWaitSemaphore());
		mDefaultRasterPass->Begin();
	}

	void VKContext::EndFrame()
	{
		mDefaultRasterPass->End();
		VK_CONTEXT->GetSwapChain()->Present(mDefaultRasterPass->GetSignalSemaphore());
		mCurFrameIdx = (mCurFrameIdx + 1) % VK_CONTEXT->GetSwapChain()->GetTextures().size();
	}

	const VKRasterPass *VKContext::GetCurRasterPass() const
	{
		return mCurRasterPass;
	}

	size_t VKContext::GetCurFrameIdx() const
	{
		return mCurFrameIdx;
	}
}