#include "GLTexture.h"
#include <vector>
#include "GLUtils.h"
namespace mulberry
{

	GLTexture::GLTexture()
	{
		glGenTextures(1, &mTextureID);
	}

	GLTexture::GLTexture(const TextureInfo &info)
		: mInfo(info)
	{
		glGenTextures(1, &mTextureID);
		CreateFrom(info);
	}

	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &mTextureID);
	}

	uint32_t GLTexture::GetHandle() const
	{
		return mTextureID;
	}

	void GLTexture::CreateFrom(const TextureInfo &info)
	{
		mInfo = info;

		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ToGLWarpMode(mInfo.wrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ToGLWarpMode(mInfo.wrapT));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ToGLFilterMode(mInfo.filterMode));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ToGLFilterMode(mInfo.filterMode));
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &mInfo.borderColor.values[0]);

		uint32_t internalFormat;
		uint32_t externalFormat;

		switch (mInfo.data.channel)
		{
		case 1:
			internalFormat = GL_R8;
			externalFormat = GL_R;
			break;
		case 2:
			internalFormat = GL_RG8;
			externalFormat = GL_RG;
			break;
		case 3:
			internalFormat = GL_RGB8;
			externalFormat = GL_RGB;
			break;
		default:
			internalFormat = GL_RGBA8;
			externalFormat = GL_RGBA;
			break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mInfo.data.width, mInfo.data.height, 0, externalFormat, GL_UNSIGNED_BYTE, mInfo.data.pixels.data());

		if (mInfo.filterMode == FilterMode::TRILINEAR)
			glGenerateTextureMipmap(mTextureID);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLTexture::CreateFromSurface(SDL_Surface *surface)
	{
		TextureInfo info;
		info.data.width = surface->w;
		info.data.height = surface->h;
		info.data.pixels = std::vector<uint8_t>((uint8_t *)surface->pixels, (uint8_t *)surface->pixels + (surface->w * surface->h * 4));
		info.borderColor = Color::Transparent;
		info.filterMode = FilterMode::LINEAR;
		CreateFrom(info);
	}

	const TextureInfo &GLTexture::GetCreateInfo() const
	{
		return mInfo;
	}
}