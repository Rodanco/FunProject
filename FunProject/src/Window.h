#pragma once
#include "SDL/SDL_video.h"
#include "SDL/SDL_render.h"
#include "SDL/SDL_events.h"
#include "Structs/Vector2.hpp"

class Window final
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	Vector2<int> pos, size;
	bool isMinimized, close;
public:
	Window();
	Window(Uint32 width, Uint32 height);
	Window(Uint32 posX, Uint32 posY, Uint32 width, Uint32 height);
	~Window();

	void HandleEvents(const SDL_Event& e);
	void ClearWindow();
	void Draw();

	bool IsToClose();
};

