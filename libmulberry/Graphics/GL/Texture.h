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
		uint32_t width = 0, height = 0,channel=4;
	};
}

namespace mulberry::GL
{
	enum class WrapMode
	{
		REPEAT,
		MIRROR_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER,
	};

	enum class FilterMode
	{
		NEAREST,
		LINEAR,
		TRILINEAR,
	};

	enum class ChannelMode
	{
		R8,
		RG8,
		RGB8,
		RGBA8,
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
		void UnBindFrom(uint32_t textureIndex) const;

		uint32_t GetID() const;
		const TextureInfo &GetCreateInfo() const;

	private:
		uint32_t WarpModeMap(WrapMode mode);
		uint32_t FilterModeMap(FilterMode mode);

		uint32_t mTextureID;
		TextureInfo mInfo;
	};
}