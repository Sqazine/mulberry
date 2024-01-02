#include "RasterPass.h"
#include "App.h"
namespace mulberry
{
	RasterPass::RasterPass(const Vec2& extent, Format format, const std::vector<Texture*>& textureLists)
	{
		GRAPHICS_RHI_IMPL_SWITCHER({
			std::vector<vk::Texture*> rawVkTextureImpls(textureLists.size());
			for (int32_t i = 0; i < textureLists.size(); ++i)
				rawVkTextureImpls[i] = textureLists[i]->mVKTextureImpl.get();

			mVKRasterPassImpl = std::make_unique<vk::RasterPass>(extent,format, rawVkTextureImpls); })
	}

	RasterPass::~RasterPass()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKRasterPassImpl.reset(nullptr))
	}

	void RasterPass::SetClearColor(const Color& clearColor)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKRasterPassImpl->SetClearColor(clearColor))
	}
	void RasterPass::IsClearColorBuffer(bool isClear)
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKRasterPassImpl->IsClearColorBuffer(isClear))
	}

	void RasterPass::Begin()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKRasterPassImpl->Begin())
	}
	void RasterPass::End()
	{
		GRAPHICS_RHI_IMPL_SWITCHER(mVKRasterPassImpl->End())
	}
}