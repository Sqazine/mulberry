#include "GraphicsContext.h"
#include <iostream>
#include "Device.h"
#include "SwapChain.h"
#include "Command.h"

#include "Graphics/RHI/GraphicsContext.h"
#include "RasterPass.h"
#include "App.h"
namespace mulberry::rhi::vk
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

	void GraphicsContext::BeginFrame()
	{
		if (App::GetInstance().GetWindow()->IsResize())
		{
			mSwapChain->ReBuild();
			mDefaultRasterPass->ReBuild(mSwapChain->GetTextures());
		}

		mSwapChain->AcquireNextImage(mDefaultRasterPass->GetWaitSemaphore());
	}

	void GraphicsContext::EndFrame()
	{
		auto result = mSwapChain->Present(mDefaultRasterPass->GetSignalSemaphore());
		mCurFrameIdx = (mCurFrameIdx + 1) % mSwapChain->GetTextures().size();

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