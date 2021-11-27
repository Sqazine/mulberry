#include "Texture.h"
#include <vector>
#include "Context.h"
namespace Pe2::GL
{

	Texture::Texture()
	{
		glGenTextures(1, &m_TextureID);
	}

	Texture::Texture(const TextureCreateInfo &info)
		: m_Info(info)
	{
		glGenTextures(1, &m_TextureID);
		CreateFrom(info);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture::BindTo(uint32_t uniform, uint32_t texIndex)
	{
		glUniform1i(uniform, texIndex);
		glActiveTexture(GL_TEXTURE0 + texIndex);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::UnBindFrom(uint32_t textureIndex)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	uint32_t Texture::GetID()
	{
		return m_TextureID;
	}

	void Texture::CreateFrom(const TextureCreateInfo &info)
	{
		m_Info = info;

		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WarpModeMap(m_Info.wrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WarpModeMap(m_Info.wrapT));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterModeMap(m_Info.filterMode));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterModeMap(m_Info.filterMode));
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &m_Info.borderColor.values[0]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Info.data.width, m_Info.data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Info.data.pixels.data());

		if (m_Info.filterMode == FilterMode::TRILINEAR)
			glGenerateTextureMipmap(m_TextureID);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	const TextureCreateInfo &Texture::GetCreateInfo()
	{
		return m_Info;
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