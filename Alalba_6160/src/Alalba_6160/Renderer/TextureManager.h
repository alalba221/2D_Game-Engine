#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "Alalba_6160/core/Base.h"
namespace Alalba{
	enum  TextureId {
		EMPTY = 0,
		AWESOMEFACE,
		AWESOMEFACEINV,
		ARROW,
		TABLE

	};

	class TextureManager {

	public:
		explicit TextureManager(SDL_Renderer* renderer);

		void renderTexture(TextureId textureId, SDL_Rect& dstRect, double angle, bool flipH = false, bool flipV = false);

		SDL_Texture* texture;
		SDL_Texture* texture2;
		SDL_Texture* textureArrow;
		SDL_Texture* textureBoard;

		~TextureManager();

	private:

		SDL_Renderer* renderer;

		std::unordered_map<TextureId, SDL_Rect*> textures{};
		std::unordered_map<TextureId, SDL_Texture*> ShuffleBoardTextures{};
	};
}