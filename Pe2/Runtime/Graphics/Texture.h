#pragma once
#include <cstdint>
#include <string>
#include <glad/glad.h>
#include <vector>
#include "../Math/Color.h"
namespace Pe2
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
		RGB8,
		RGBA8,
	};

	struct ImgData
	{
		std::vector<uint8_t> pixels{};
		uint32_t width = 0, height = 0;
	};

	struct TextureInfo
	{
		WrapMode wrapS = WrapMode::REPEAT, wrapT = WrapMode::REPEAT;
		FilterMode filterMode;
		Color borderColor = Color::BLACK;
		ImgData data;
	};
	class Texture
	{
	public:
		Texture();
		Texture(const TextureInfo &info);
		~Texture();

		void CreateFrom(const TextureInfo &info);

		void BindTo(uint32_t uniform, uint32_t texIndex);
		void UnBindFrom(uint32_t textureIndex);

		uint32_t GetID();
		const TextureInfo &GetCreateInfo();

	private:
		uint32_t WarpModeMap(WrapMode mode);
		uint32_t FilterModeMap(FilterMode mode);

		uint32_t m_TextureID;
		TextureInfo m_Info;
	};
}