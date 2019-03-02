#pragma once
#include <functional>
#include "SDL/SDL_video.h"
#include "SDL/SDL_render.h"
#include "SDL/SDL_events.h"
#include "Structs/Vector2.hpp"

class Window final
{
	std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
	std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> renderer;

	Vector2<int> pos, currentSize, beforeFullscreenSize;
	bool isMinimized, close, hasResize, fullscreen;
	int windowID;

public:
	Window();
	Window(Uint32 width, Uint32 height);
	Window(Uint32 posX, Uint32 posY, Uint32 width, Uint32 height);
	~Window() = default;

	void HandleEvents(const SDL_Event& e);
	void ClearWindow();
	void Draw();

	void ToogleFullscreen();

	bool IsToClose()const;
	/// <summary>
	/// Verify if Window has resized.
	/// </summary>
	/// <param name="newSize">The new size window return value.</param>
	/// <returns>
	///   <c>true</c> if the window has resized; otherwise, <c>false</c>.
	/// </returns>
	bool HasResized(Vector2<int>* newSize = nullptr)const;
};

