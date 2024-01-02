#include "Context.h"
#include <iostream>
#include "Device.h"
#include "SwapChain.h"
#include "CommandPool.h"
#include "CommandBuffer.h"
#include "Graphics/RHI/GraphicsContext.h"
#include "RasterPass.h"
#include "App.h"
namespace mulberry::vk
{
	Context::Context()
	{
	}
	Context::~Context()
	{
	}

	void Context::Init()
	{
		mAdapter = std::make_unique<Adapter>();

#ifdef _DEBUG
		mAdapter->PrintInstanceInfo();
		mAdapter->PrintPhysicalDeviceSpecs();
#endif
		mDevice.reset(mAdapter->CreateDevice());
		mSwapChain = std::make_unique<SwapChain>();

		mDefaultRasterPass = std::make_unique<RasterPass>(mSwapChain->GetExtent(),
			mSwapChain->GetSurfaceFormat().format,
			mSwapChain->GetTextures());
	}

	Adapter *Context::GetAdapter() const
	{
		return mAdapter.get();
	}

	Device *Context::GetDevice() const
	{	
		return mDevice.get();
	}

	SwapChain *Context::GetSwapChain() const
	{
		return mSwapChain.get();
	}

	void Context::SetClearColor(const Color &clearColor)
	{
		mDefaultRasterPass->SetClearColor(clearColor);
	}

	void Context::IsClearColorBuffer(bool isClear)
	{
		mDefaultRasterPass->IsClearColorBuffer(isClear);
	}

	void Context::BeginFrame()
	{
		if (App::GetInstance().GetWindow()->IsResize())
		{
			mSwapChain->ReBuild();
			mDefaultRasterPass->ReBuild(mSwapChain->GetExtent(), mSwapChain->GetTextures());
		}

		mSwapChain->AcquireNextImage(mDefaultRasterPass->GetWaitSemaphore());
		mDefaultRasterPass->Begin();
	}

	void Context::EndFrame()
	{
		mDefaultRasterPass->End();
		mSwapChain->Present(mDefaultRasterPass->GetSignalSemaphore());
		mCurFrameIdx = (mCurFrameIdx + 1) % mSwapChain->GetTextures().size();
	}

	const RasterPass *Context::GetCurRasterPass() const
	{
		return mCurRasterPass;
	}

	size_t Context::GetCurFrameIdx() const
	{
		return mCurFrameIdx;
	}
}