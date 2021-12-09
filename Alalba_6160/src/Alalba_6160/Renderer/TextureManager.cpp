#include "TextureManager.h"
namespace Alalba{
	TextureManager::TextureManager(SDL_Renderer* renderer) : renderer{renderer} \
	{
		SDL_Surface* tempSurface = IMG_Load("../../../asset/red_puck.png");
		if (!tempSurface) {
				std::cout << "[Texture manager] Unable to load texture: " << IMG_GetError() << std::endl;
				throw std::invalid_argument("Unable to load texture");
		}
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		//textures.insert_or_assign(TextureId::RED, new SDL_Rect{12*17, 4*17, TILE_SIZE, TILE_SIZE});
		ShuffleBoardTextures.insert_or_assign(TextureId::RED, texture);		
		
		// Add arrow and board images
		tempSurface = IMG_Load("../../../asset/arrow.png");
		textureArrow = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		ShuffleBoardTextures.insert_or_assign(TextureId::ARROW, textureArrow);

		//
		// Add inverse face
		tempSurface = IMG_Load("../../../asset/blue_puck.png");
		texture2 = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		ShuffleBoardTextures.insert_or_assign(TextureId::BLUE, texture2);		


		tempSurface = IMG_Load("../../../asset/table.png");
		textureBoard = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		ShuffleBoardTextures.insert_or_assign(TextureId::TABLE, textureBoard);		
		// textures.insert_or_assign(TextureId::ARROW, new SDL_Rect{12*17, 4*17, TILE_SIZE, TILE_SIZE});
	}

	void TextureManager::renderTexture(TextureId textureId, SDL_Rect& dstRect, double angle, bool flipH, bool flipV) {
		auto txt = ShuffleBoardTextures.find(textureId);
		if (txt != ShuffleBoardTextures.end()) {
			// if (dstRect.w == 0) dstRect.w = TILE_SIZE;
			// if (dstRect.h == 0) dstRect.h = TILE_SIZE;
			SDL_RenderCopyEx(renderer, txt->second, NULL, &dstRect, angle, nullptr,
											(SDL_RendererFlip) (SDL_FLIP_NONE | (SDL_FLIP_HORIZONTAL * flipH) |
																					(SDL_FLIP_VERTICAL * flipV)));
		}
	}

	TextureManager::~TextureManager() {
		std::unordered_map<TextureId, SDL_Rect*>::iterator it;
		for (it = textures.begin(); it != textures.end(); ++it) delete it->second;
	}
}