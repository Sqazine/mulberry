#pragma once
#include <vector>
#include <cstdint>
#include <vector>
#include <cstdint>
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
}