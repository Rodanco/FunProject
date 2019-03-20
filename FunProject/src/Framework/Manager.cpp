#include "Manager.h"
#include "SDL/SDL_timer.h"

void Manager::Cleaning()
{
	dmWindow->ClearWindow();
	//playersWindow->ClearWindow();
}

void Manager::PreUpdate(float deltaTime)
{
}

void Manager::Update(float deltaTime)
{
}

void Manager::Rendering()
{
	dmWindow->Draw();
}

void Manager::InputThread()
{
	SDL_Event even;
	int numberOfEvents;
	while (!quit.load(std::memory_order::memory_order_acquire))
	{
		numberOfEvents = SDL_PeepEvents(&even, 10, SDL_GETEVENT, SDL_DISPLAYEVENT, SDL_WINDOWEVENT);
		if (numberOfEvents > 0)
		{
			//playersWindow->HandleEvents(sdlEvents);
			dmWindow->HandleEvents(even);
		}
		
		std::this_thread::yield();
	}
}

Manager::Manager(): dmWindow(std::make_unique<Window>())/*, playersWindow(std::make_unique<Window>(1920, 0, 1280, 720))*/,
					maxFPS(60), msMaxFPS(1000.f/60), quit(false)
{
}

Manager::~Manager()
{
}

void Manager::Run()
{
	Uint32 startLoop = SDL_GetTicks();
	Uint32 endLoop = SDL_GetTicks();
	float deltaTime;
	inputThread = std::thread(&Manager::InputThread, this);
	while (!quit.load(std::memory_order::memory_order_acquire))
	{
		deltaTime = static_cast<float>(endLoop - startLoop);
		/*if (deltaTime < msMaxFPS)
		{
			SDL_Delay(deltaTime = (msMaxFPS - deltaTime));
		}*/
		startLoop = SDL_GetTicks();
		SDL_PumpEvents();
		Cleaning();
		PreUpdate(deltaTime);
		Update(deltaTime);
		Rendering();
		std::this_thread::yield();
		endLoop = SDL_GetTicks();
	}
	inputThread.join();
}
