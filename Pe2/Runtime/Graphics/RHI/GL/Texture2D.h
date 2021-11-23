#pragma once
#include <cstdint>
#include <string>
#include <glad/glad.h>
#include "Context.h"
#include "../../../Math/Color.h"
namespace GL
{
	enum WrapMode
	{
		REPEAT = GL_REPEAT,
		MIRROR_REPEAT = GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
	};

	enum FilterMode
	{
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR,
		TRILINEAR=GL_LINEAR_MIPMAP_LINEAR,
	};

	enum ChannelMode
	{
		RGB8 = GL_RGB8,
		RGBA8 = GL_RGBA8,
	};

	struct Texture2DCreateInfo
	{
		int32_t wrapS = WrapMode::REPEAT, wrapT = WrapMode::REPEAT;
		int32_t minFilter = FilterMode::LINEAR, magFilter = FilterMode::LINEAR;
		Color4 borderColor = Color4::BLACK;
		Vec2 extent = Vec2::ZERO;
		ChannelMode channelMode = ChannelMode::RGBA8;
		void *data = nullptr;
	};

	class Texture2D
	{
	public:
		Texture2D();
		Texture2D(const Texture2DCreateInfo &info);
		~Texture2D();

		void CreateFrom(const Texture2DCreateInfo &info);

		void BindTo(uint32_t uniform, uint32_t texIndex);
		void UnBindFrom(uint32_t textureIndex);

		uint32_t GetID();
		const Texture2DCreateInfo &GetCreateInfo();

	protected:
		uint32_t m_TextureID;
		Texture2DCreateInfo m_Info;
	};
}