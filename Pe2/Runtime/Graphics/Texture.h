#pragma once

#include <memory>
#include "../Math/Color.h"
#include "TextureInfo.h"
#include "GL/Texture.h"
namespace Pe2
{
	class Texture
	{
	public:
		Texture(const TextureInfo &info);
		~Texture();

	private:
		std::unique_ptr<GL::Texture> m_GLTexture;
	};
}