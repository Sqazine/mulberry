#pragma once
#include "Graphics/RHI/Defs.h"
#include "Graphics/RHI/Texture.h"
#include "Graphics/RHI/Utils.h"
namespace mulberry
{
	class ColorAttachment
	{
	public:
		ColorAttachment() = default;
		virtual ~ColorAttachment() = default;

		ColorAttachment &SetClearColor(const Color &color)
		{
			SET(mClearColor, color);
		}
		const Color &GetClearColor() const
		{
			return mClearColor;
		}

		ColorAttachment &SetLoadOp(AttachmentLoad loadOp)
		{
			SET(mLoadOp, loadOp);
		}
		const AttachmentLoad &GetLoadOp() const
		{
			return mLoadOp;
		}

		ColorAttachment &SetStoreOp(AttachmentStore storeOp)
		{
			SET(mStoreOp, storeOp);
		}
		const AttachmentStore &GetStoreOp() const
		{
			return mStoreOp;
		}

		ColorAttachment &SetTexture(Texture *texture)
		{
			SET_UNIQUE_PTR(mTexture,texture);
		}
		
		Texture *GetTexture() const
		{
			return mTexture.get();
		}

	protected:
		std::unique_ptr<Texture> mTexture;
		Color mClearColor;
		AttachmentLoad mLoadOp;
		AttachmentStore mStoreOp;

		bool mIsDirty{true};
	};
}