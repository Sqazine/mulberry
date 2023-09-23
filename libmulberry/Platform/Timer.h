#pragma once

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include "SDL2Wrapper/SDL2Timer.h"
#else
#endif

namespace mulberry
{
    class Timer
    {
    public:
    Timer();
    void Init();
		void Update(uint32_t lockFrame = 0);

		float GetDeltaTime();
    private:
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        SDL2Timer mSDL2TimerImpl;
#else
#error "Unknown platform Timer"
#endif
    };
}