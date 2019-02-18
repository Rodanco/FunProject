#pragma once
#include "SDL/SDL_timer.h"

struct Timer final
{
	Timer() : paused(false), started(true), startTick(SDL_GetTicks()), pausedTick(0)
	{
	}
	~Timer() = default;

	void Stop()
	{
		started = false;
		paused = false;
		startTick = 0;
		pausedTick = 0;
	}

	void Pause()
	{
		if (!started || paused)
			return;

		pausedTick = SDL_GetTicks() - startTick;
		startTick = 0;
		paused = true;
	}

	void Unpause()
	{
		if (!started || !paused)
			return;
		paused = false;
		startTick = SDL_GetTicks() - pausedTick;
		pausedTick = 0;
	}

	Uint32 GetTicks()
	{
		if (!started)
			return;
		if (paused)
			return pausedTick;
		return SDL_GetTicks() - startTick;
	}

	bool paused, started;
private:
	Uint32 startTick, pausedTick;
};