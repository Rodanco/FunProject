#pragma once
#include "Structs/Vector2.hpp"
#include "SDL/SDL_rect.h"
#include "SDL/SDL_render.h"
#include <functional>


struct Sprite final
{
	AtomicVec2u size;
	std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>> texture;
	Sprite(std::string_view textureFile);
};
