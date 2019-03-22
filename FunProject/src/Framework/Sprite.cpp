#include "Sprite.h"
#include "SDL/SDL_image.h"

Sprite::Sprite(std::string_view textureFile)
{
	texture = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>>
		(
			IMG_LoadTex
		);
}
