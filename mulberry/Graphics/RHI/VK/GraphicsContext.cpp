#include "GraphicsContext.h"
#include <iostream>
#include "Device.h"
#include "SwapChain.h"
#include "Command.h"
#include "RasterPass.h"
#include "App.h"
namespace mulberry::rhi::vk
{
	GraphicsContext::GraphicsContext()
		: mCurFrameIdx(0)
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
		mSwapChain = std::make_unique<SwapChain>();

		mDefaultRasterPass = std::make_unique<RasterPass>(mSwapChain->GetTextures());
	}

	Adapter *GraphicsContext::GetAdapter() const
	{
		return mAdapter.get();
	}

	Device *GraphicsContext::GetDevice() const
	{
		return mDevice.get();
	}

	SwapChain *GraphicsContext::GetSwapChain() const
	{
		return mSwapChain.get();
	}

	void GraphicsContext::SetClearColor(const Color &clearColor)
	{
		mDefaultRasterPass->SetClearColor(clearColor);
	}

	void GraphicsContext::IsClearColorBuffer(bool isClear)
	{
		mDefaultRasterPass->IsClearColorBuffer(isClear);
	}

	void GraphicsContext::BeginFrame()
	{
		if (App::GetInstance().GetWindow()->IsResize())
		{
			mSwapChain->ReBuild();
			mDefaultRasterPass->ReBuild(mSwapChain->GetTextures());
			mCurFrameIdx = 0;
		}

		mSwapChain->AcquireNextImage(mDefaultRasterPass->GetWaitSemaphore());

		mDefaultRasterPass->Begin();
	}

	void GraphicsContext::EndFrame()
	{
		mDefaultRasterPass->End();

		auto result = mSwapChain->Present(mDefaultRasterPass->GetSignalSemaphore());
		mDevice->GetPresentQueue()->WaitIdle();
		
		mCurFrameIdx = (mCurFrameIdx + 1) % ((int32_t)mSwapChain->GetTextures().size());

		if (result != VK_SUCCESS)
		{
			mSwapChain->ReBuild();
			mDefaultRasterPass->ReBuild(mSwapChain->GetTextures());
			mCurFrameIdx = 0;
		}
	}

	const RasterPass *GraphicsContext::GetDefaultRasterPass() const
	{
		return mDefaultRasterPass.get();
	}

	size_t GraphicsContext::GetCurFrameIdx() const
	{
		return mCurFrameIdx;
	}
}