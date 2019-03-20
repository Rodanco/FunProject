#pragma once
#include "Window.h"
#include "Definitions.h"
#include <thread>
#include <atomic>

class Manager final
{
	std::unique_ptr<Window> dmWindow, playersWindow;
	Uint32 maxFPS;
	float msMaxFPS;
	std::atomic_bool quit;
	std::thread inputThread;
	std::atomic_int atomicDeltaTime;

	void Cleaning();
	void PreUpdate(float deltaTime);
	void Update(float deltaTime);	
	void Rendering();

	void InputThread();

public:
	Manager();
	~Manager();
	void Run();
};