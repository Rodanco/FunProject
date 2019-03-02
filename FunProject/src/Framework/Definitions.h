#include "SDL/SDL_log.h"
#if DEBUG
#define ONLY_DEBUG(x) x
#define LOG(msg, ...) SDL_Log(msg, __VA_ARGS__)
#else
#define ONLY_DEBUG(x)
#define LOG(msg, ...)
#endif