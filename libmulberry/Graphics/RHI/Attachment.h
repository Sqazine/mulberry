#pragma once
#include <vulkan/vulkan.h>
#include "Graphics/RHI/Defs.h"
#include "Graphics/RHI/Texture.h"

namespace mulberry
{
	struct ColorAttachment
	{
		ColorAttachment()=default;
		~ColorAttachment()
		{
			SAFE_DELETE(texture);
		}
		Texture *texture;
		Color clearColor;
		AttachmentLoad loadOp;
		AttachmentStore storeOp;
	};
}