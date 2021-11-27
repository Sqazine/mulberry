#pragma once
#include <cstdint>
#include <string>
#include <glad/glad.h>
#include "Context.h"
#include "../../Math/Color.h"
#include "../Texture.h"
namespace Pe2::GL
{
	class Texture
	{
	public:
		Texture();
		Texture(const TextureCreateInfo &info);
		~Texture();

		void CreateFrom(const TextureCreateInfo &info);

		void BindTo(uint32_t uniform, uint32_t texIndex);
		void UnBindFrom(uint32_t textureIndex);

		uint32_t GetID();
		const TextureCreateInfo &GetCreateInfo();

	private:
		uint32_t WarpModeMap(WrapMode mode);
		uint32_t FilterModeMap(FilterMode mode);

		uint32_t m_TextureID;
		TextureCreateInfo m_Info;
	};
}