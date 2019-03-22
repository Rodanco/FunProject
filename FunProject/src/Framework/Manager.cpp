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
	SDL_Event e;
	while (!quit.load(std::memory_order_acquire))
	{
		if (SDL_PeepEvents(&e, 10, SDL_GETEVENT, SDL_DISPLAYEVENT, SDL_MOUSEWHEEL) > 0)
		{
			dmWindow->HandleEvents(e);
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
	std::thread inputThread = std::thread(&Manager::InputThread, this);
	while (!quit.load(std::memory_order_acquire))
	{
		deltaTime = static_cast<float>(endLoop - startLoop);
		/*if (deltaTime < msMaxFPS)
		{
			LOG("Real deltaTime: %f\tLocked deltaTime: %f", deltaTime, (msMaxFPS - deltaTime));
			SDL_Delay(deltaTime = (msMaxFPS - deltaTime));
		}*/
		startLoop = SDL_GetTicks();
		Cleaning();
		SDL_PumpEvents();
		PreUpdate(deltaTime);
		Update(deltaTime);
		Rendering();
		endLoop = SDL_GetTicks();
		std::this_thread::yield();
	}
	inputThread.join();
}
