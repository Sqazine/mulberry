#include "Texture.h"
#include <vector>

namespace Pe2::GL
{

	Texture::Texture()
	{
		glGenTextures(1, &mTextureID);
	}

	Texture::Texture(const TextureInfo &info)
		: mInfo(info)
	{
		glGenTextures(1, &mTextureID);
		CreateFrom(info);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &mTextureID);
	}

	void Texture::BindTo(uint32_t uniform, uint32_t texIndex) const
	{
		glUniform1i(uniform, texIndex);
		glActiveTexture(GL_TEXTURE0 + texIndex);
		glBindTexture(GL_TEXTURE_2D, mTextureID);
	}

	void Texture::UnBindFrom(uint32_t textureIndex) const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	uint32_t Texture::GetID() const
	{
		return mTextureID;
	}

	void Texture::CreateFrom(const TextureInfo &info)
	{
		mInfo = info;

		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WarpModeMap(mInfo.wrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WarpModeMap(mInfo.wrapT));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterModeMap(mInfo.filterMode));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterModeMap(mInfo.filterMode));
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &mInfo.borderColor.values[0]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mInfo.data.width, mInfo.data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mInfo.data.pixels.data());

		if (mInfo.filterMode == FilterMode::TRILINEAR)
			glGenerateTextureMipmap(mTextureID);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::CreateFromSurface(SDL_Surface *surface)
	{
		TextureInfo info;
		info.data.width = surface->w;
		info.data.height = surface->h;
		info.data.pixels = std::vector<uint8_t>((uint8_t *)surface->pixels, (uint8_t *)surface->pixels + (surface->w * surface->h * 4));
		info.borderColor = Color::Transparent;
		info.filterMode = FilterMode::LINEAR;
		CreateFrom(info);
	}

	const TextureInfo &Texture::GetCreateInfo() const
	{
		return mInfo;
	}

	uint32_t Texture::WarpModeMap(WrapMode mode)
	{
		switch (mode)
		{
		case WrapMode::REPEAT:
			return GL_REPEAT;
		case WrapMode::MIRROR_REPEAT:
			return GL_MIRRORED_REPEAT;
		case WrapMode::CLAMP_TO_EDGE:
			return GL_CLAMP_TO_EDGE;
		case WrapMode::CLAMP_TO_BORDER:
			return GL_CLAMP_TO_BORDER;
		default:
			return GL_REPEAT;
		}
	}
	uint32_t Texture::FilterModeMap(FilterMode mode)
	{
		switch (mode)
		{
		case FilterMode::NEAREST:
			return GL_NEAREST;
		case FilterMode::LINEAR:
			return GL_LINEAR;
		case FilterMode::TRILINEAR:
			return GL_LINEAR_MIPMAP_LINEAR;
		default:
			return GL_NEAREST;
		}
	}
}