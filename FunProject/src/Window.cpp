#include "Window.h"
#include <string>
#include "SDL/SDL_log.h"

#define VNAME(x) #x

Window::Window() : Window(1280, 720)
{
}

Window::Window(Uint32 width, Uint32 height) : Window(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height)
{
}

Window::Window(Uint32 posX, Uint32 posY, Uint32 width, Uint32 height)
	: window(nullptr), renderer(nullptr), pos(), size(), isMinimized(false), close(false)
{
	window = SDL_CreateWindow("Test", posX, posY, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	SDL_GetWindowPosition(window, &pos.x, &pos.y);
	size.x = width;
	size.y = height;
}


Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Window::HandleEvents(const SDL_Event & e)
{
	if (e.type != SDL_WINDOWEVENT)
		return;
	std::string logText = " Window " + std::to_string(SDL_GetWindowID(window));
	auto& windowEvent = e.window;
	switch (windowEvent.event)
	{
	case SDL_WINDOWEVENT_CLOSE:
		close = true;
		logText += " started to close";
		break;
	case SDL_WINDOWEVENT_MINIMIZED:
		isMinimized = true;
		logText += " minimized.";
		break;
	case SDL_WINDOWEVENT_RESTORED:
		isMinimized = false;
		logText += " restored.";
		break;
	case SDL_WINDOWEVENT_RESIZED:
		size.x = windowEvent.data1;
		size.y = windowEvent.data2;
		SDL_RenderPresent(renderer);
		logText += " resized to ";
		logText += size.ToText();
		break;
	case SDL_WINDOWEVENT_MOVED:
		pos.x = windowEvent.data1;
		pos.y = windowEvent.data2;
		logText += " moved to position ";
		logText += pos.ToText();
		break;
	}
#if DEBUG
	SDL_Log(logText.data());
#endif
}

void Window::ClearWindow()
{
	SDL_RenderClear(renderer);
}

void Window::Draw()
{
	if (!isMinimized)
		SDL_RenderPresent(renderer);
}

bool Window::IsToClose()
{
	return close;
}
