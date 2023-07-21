#pragma once
#include <cstdint>
#include <string>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <vector>
#include "Math/Color.h"

namespace mulberry
{
	struct ImgData
	{
		std::vector<uint8_t> pixels{};
		uint32_t width = 0, height = 0, channel = 4;
	};
}

namespace mulberry::gl
{
	enum class WrapMode
	{
		REPEAT = GL_REPEAT,
		MIRROR_REPEAT = GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
	};

	enum class FilterMode
	{
		NEAREST=GL_NEAREST,
		LINEAR=GL_LINEAR,
		TRILINEAR=GL_LINEAR_MIPMAP_LINEAR,
		NEAREST_MIPMAP_NEAREST=GL_NEAREST_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR=GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_NEAREST=GL_LINEAR_MIPMAP_NEAREST
	};

	enum class ChannelMode
	{
		R8 = GL_R8,
		RG8 = GL_RG8,
		RGB8 = GL_RGB8,
		RGBA8 = GL_RGBA8,

		R16F = GL_R16F,
		RG16F = GL_RG16F,
		RGB16F = GL_RGB16F,
		RGBA16F = GL_RGBA16F,

		R32F = GL_R32F,
		RG32F = GL_RG32F,
		RGB32F = GL_RGB32F,
		RGBA32F = GL_RGBA32F,
	};

	struct TextureInfo
	{
		WrapMode wrapS = WrapMode::REPEAT, wrapT = WrapMode::REPEAT;
		FilterMode filterMode = FilterMode::NEAREST;
		Color borderColor = Color::Black;
		ImgData data;
	};
	class Texture
	{
	public:
		Texture();
		Texture(const TextureInfo &info);
		~Texture();

		void CreateFrom(const TextureInfo &info);
		void CreateFromSurface(SDL_Surface *surface);

		void BindTo(uint32_t uniform, uint32_t texIndex) const;
		void UnBind() const;

		uint32_t GetID() const;
		const TextureInfo &GetCreateInfo() const;

	private:
		uint32_t WarpModeMap(WrapMode mode);
		uint32_t FilterModeMap(FilterMode mode);

		uint32_t mTextureID;
		TextureInfo mInfo;
	};
}