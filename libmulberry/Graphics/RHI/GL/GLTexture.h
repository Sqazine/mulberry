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

		uint32_t GetHandle() const;
		const TextureInfo &GetCreateInfo() const;

	private:
		uint32_t mTextureID;
		TextureInfo mInfo;
	};
}