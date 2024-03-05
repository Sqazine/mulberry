#include "GraphicsContext.h"
#include <iostream>
#include "Device.h"
#include "SwapChain.h"
#include "Command.h"
#include "Pass.h"
#include "App.h"
#include "Graphics/RHI/Pass.h"
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
	}

	void GraphicsContext::Destroy()
	{
		mSwapChain.reset(nullptr);
		mDevice.reset(nullptr);
		mAdapter.reset(nullptr);
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
			mCurFrameIdx = 0;
		}

		auto vkDefaultDrawPassImpl = App::GetInstance().GetGraphicsContext()->GetDefaultDrawPass()->GetVkImpl();

		mSwapChain->AcquireNextImage(vkDefaultDrawPassImpl->GetWaitSemaphore());
	}

	void GraphicsContext::EndFrame()
	{
		auto vkDefaultDrawPassImpl = App::GetInstance().GetGraphicsContext()->GetDefaultDrawPass()->GetVkImpl();

		auto result = mSwapChain->Present(vkDefaultDrawPassImpl->GetSignalSemaphore());
		mDevice->GetPresentQueue()->WaitIdle();

		mCurFrameIdx = (mCurFrameIdx + 1) % ((int32_t)mSwapChain->GetTextures().size());

		if (result != VK_SUCCESS)
		{
			mSwapChain->ReBuild();
			mCurFrameIdx = 0;
		}
	}

	size_t GraphicsContext::GetCurFrameIdx() const
	{
		return mCurFrameIdx;
	}
}