#include "Texture2D.h"
#include <vector>
#include "Context.h"
namespace GL
{

	Texture2D::Texture2D()
	{
		glGenTextures(1, &m_TextureID);
	}

	Texture2D::Texture2D(const Texture2DCreateInfo &info)
		: m_Info(info)
	{
		glGenTextures(1, &m_TextureID);
		CreateFrom(info);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture2D::BindTo(uint32_t uniform, uint32_t texIndex)
	{
		glUniform1i(uniform, texIndex);
		glActiveTexture(GL_TEXTURE0 + texIndex);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture2D::UnBindFrom(uint32_t textureIndex)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	uint32_t Texture2D::GetID()
	{
		return m_TextureID;
	}

	void Texture2D::CreateFrom(const Texture2DCreateInfo &info)
	{
		m_Info = info;
		uint32_t externalFormat = GL_RED, internalFormat = GL_R8, channelType = GL_UNSIGNED_BYTE;
		switch (info.channelMode)
		{
		case ChannelMode::RGB8:
			externalFormat = GL_RGB;
			internalFormat = GL_RGB8;
			channelType = GL_UNSIGNED_BYTE;
			break;
		case ChannelMode::RGBA8:
			externalFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
			channelType = GL_UNSIGNED_BYTE;
			break;
		default:
			break;
		}

		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_Info.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_Info.wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Info.minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Info.magFilter);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &m_Info.borderColor.values[0]);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Info.extent.x, m_Info.extent.y, 0, externalFormat, channelType, m_Info.data);

		if(m_Info.magFilter==FilterMode::TRILINEAR)
			glGenerateTextureMipmap(m_TextureID);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	const Texture2DCreateInfo &Texture2D::GetCreateInfo()
	{
		return m_Info;
	}
}