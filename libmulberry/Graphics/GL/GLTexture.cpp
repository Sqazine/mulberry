#include "GLTexture.h"
#include <vector>

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

	void GLTexture::BindTo(uint32_t uniform, uint32_t texIndex) const
	{
		glUniform1i(uniform, texIndex);
		glActiveTexture(GL_TEXTURE0 + texIndex);
		glBindTexture(GL_TEXTURE_2D, mTextureID);
	}

	void GLTexture::UnBind() const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
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

	uint32_t GLTexture::ToGLWarpMode(WrapMode mode)
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
	uint32_t GLTexture::ToGLFilterMode(FilterMode mode)
	{
		switch (mode)
		{
		case FilterMode::NEAREST:
			return GL_NEAREST;
		case FilterMode::LINEAR:
			return GL_LINEAR;
		case FilterMode::TRILINEAR:
			return GL_LINEAR_MIPMAP_LINEAR;
		case FilterMode::NEAREST_MIPMAP_NEAREST:
			return GL_NEAREST_MIPMAP_NEAREST;
		case FilterMode::NEAREST_MIPMAP_LINEAR:
			return GL_NEAREST_MIPMAP_LINEAR;
		case FilterMode::LINEAR_MIPMAP_NEAREST:
			return GL_LINEAR_MIPMAP_NEAREST;
		default:
			return GL_NEAREST;
		}
	}

	uint32_t GLTexture::ToGLFormat(Format mode)
	{
		switch (mode)
		{
		case Format::R8:
			return GL_R8;
		case Format::RG8:
			return GL_RG8;
		case Format::RGB8:
			return GL_RGB8;
		case Format::RGBA8:
			return GL_RGBA8;
		case Format::R16F:
			return GL_R16F;
		case Format::RG16F:
			return GL_RG16;
		case Format::RGB16F:
			return GL_RGB16F;
		case Format::R32F:
			return GL_R32F;
		case Format::RG32F:
			return GL_RG32F;
		case Format::RGB32F:
			return GL_RGB32F;
		case Format::RGBA32F:
			return GL_RGBA32F;
		default:
			break;
		}
	}
}