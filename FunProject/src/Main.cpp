#include "SDL/SDL.h"
#include "Window.h"
#include <functional>

int main(int argc, char* argv[])
{
	{
		std::unique_ptr<Window> window = std::make_unique<Window>(1280, 720);
		SDL_Event e;
		while (!window->IsToClose())
		{
			while (SDL_PollEvent(&e))
				window->HandleEvents(e);
		}
	}
	return 0;
}