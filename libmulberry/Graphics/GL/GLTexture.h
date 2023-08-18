#pragma once
#include <cstdint>
#include <string>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <vector>
#include "Math/Color.h"
#include "Texture.h"

namespace mulberry
{
	class GLTexture
	{
	public:
		GLTexture();
		GLTexture(const TextureInfo &info);
		~GLTexture();

		void CreateFrom(const TextureInfo &info);
		void CreateFromSurface(SDL_Surface *surface);

		void BindTo(uint32_t uniform, uint32_t texIndex) const;
		void UnBind() const;

		uint32_t GetHandle() const;
		const TextureInfo &GetCreateInfo() const;

	private:
		uint32_t ToGLWarpMode(WrapMode mode);
		uint32_t ToGLFilterMode(FilterMode mode);
		uint32_t ToGLFormat(Format mode);

		uint32_t mTextureID;
		TextureInfo mInfo;
	};
}