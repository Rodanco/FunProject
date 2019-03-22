#include "Window.h"
#include <string>
#include "SDL/SDL_log.h"
#include "SDL/SDL_timer.h"
#include "Definitions.h"

Window::Window() : Window(1280, 720)
{
}

Window::Window(Uint32 width, Uint32 height) : Window(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height)
{
}

Window::Window(Uint32 posX, Uint32 posY, Uint32 width, Uint32 height)
	: window(nullptr), renderer(nullptr), pos(), currentSize(Vector2i(width, height)), beforeFullscreenSize(Vector2i(width, height)),
	  isMinimized(false), close(false), hasResize(false), fullscreen(false), windowID(0)
{
	window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
		SDL_CreateWindow("Test", posX, posY, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE),
		SDL_DestroyWindow);
	renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>(
		SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED),
		SDL_DestroyRenderer);
	Vector2i aux;
	SDL_GetWindowPosition(window.get(), &aux.x, &aux.y);
	windowID.store(SDL_GetWindowID(window.get()), std::memory_order_release);
	pos.store(aux, std::memory_order_release);
	windowID = SDL_GetWindowID(window.get());
}

void Window::HandleEvents(const SDL_Event & e)
{
	if (e.type != SDL_WINDOWEVENT)
		return;
	const auto& windowEvent = e.window;
	if (windowEvent.windowID != windowID)
		return;
	ONLY_DEBUG(std::string logText = "Window " + std::to_string(SDL_GetWindowID(window.get()));)
	switch (windowEvent.event)
	{
	case SDL_WINDOWEVENT_FOCUS_LOST:
		//ONLY_DEBUG(logText += " has lost focus from user";)
		break;
	case SDL_WINDOWEVENT_FOCUS_GAINED:
		//ONLY_DEBUG(logText += " has gained focus from user";)
		break;
	case SDL_WINDOWEVENT_CLOSE:
		close.store(true, std::memory_order_release);
		LOG("Window %d closed.", SDL_GetWindowID(window.get()));
		break;
	case SDL_WINDOWEVENT_MINIMIZED:
		isMinimized.store(true, std::memory_order_release);
		LOG("Window %d minimized.", SDL_GetWindowID(window.get()));
		break;
	case SDL_WINDOWEVENT_RESTORED:
		isMinimized.store(false, std::memory_order_release);
		LOG("Window %d restored.", SDL_GetWindowID(window.get()));
		break;
	case SDL_WINDOWEVENT_RESIZED:
		currentSize.store({ windowEvent.data1, windowEvent.data2 }, std::memory_order_release);
		hasResize.store(true, std::memory_order_release);
		LOG("Window %d resized to %s.", SDL_GetWindowID(window.get()), currentSize.load(std::memory_order_acquire).ToString().data());
		break;
	case SDL_WINDOWEVENT_MOVED:
		pos.store({ windowEvent.data1, windowEvent.data2 }, std::memory_order_release);
		LOG("Window %d moved to %s.", SDL_GetWindowID(window.get()), pos.load(std::memory_order_acquire).ToString().data());
		break;
	}
}

void Window::ClearWindow()
{
	hasResize.store(false, std::memory_order_release);
	if(!isMinimized)
		SDL_RenderClear(renderer.get());
}

void Window::Draw()
{
	if (!isMinimized)
		SDL_RenderPresent(renderer.get());
}

void Window::ToogleFullscreen()
{
	if (!fullscreen.load(std::memory_order_acquire))
	{
		fullscreen.store(true, std::memory_order_release);		
		ONLY_DEBUG(
			int sucess = SDL_SetWindowFullscreen(window.get(), SDL_WINDOW_FULLSCREEN_DESKTOP);\
			if (sucess != 0)\
				SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "[ERROR VIDEO] Window %d suffered an error: %s\n", SDL_GetWindowID(window.get()), std::string(SDL_GetError())); \
			else\
			{\
				LOG("Window %d is fullscreen on display %d", SDL_GetWindowID(window.get()), SDL_GetWindowDisplayIndex(window.get())); \
				Vector2<int> s; \
				SDL_GetWindowSize(window.get(), &s.x, &s.y); \
				LOG("Window currentSize: %d, %d", s.x, s.y);
			}
		)
		return;
	}
	SDL_SetWindowFullscreen(window.get(), 0);
	//SDL_RestoreWindow(window.get());
	//SDL_SetWindowSize(window.get(), beforeFullscreenSize.x, beforeFullscreenSize.y);
	fullscreen.store(false, std::memory_order_release);
}

bool Window::IsToClose() const
{
	return close.load(std::memory_order_acquire);
}

bool Window::HasResized(Vector2<int>* newSize) const
{
	if (newSize != nullptr)
		*newSize = currentSize.load(std::memory_order_acquire);
	return hasResize.load(std::memory_order_acquire);
}
