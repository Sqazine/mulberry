#include "Timer.h"

namespace mulberry
{
    Timer::Timer()
        :
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
          mSDL2TimerImpl()
#else
#error "Unknown platform Timer"
#endif
    {
    }
    void Timer::Init()
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        mSDL2TimerImpl.Init();
#else
#error "Unknown platform Timer"
#endif
    }
    void Timer::Update(uint32_t lockFrame)
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        mSDL2TimerImpl.Update(lockFrame);
#else
#error "Unknown platform Timer"
#endif
    }

    float Timer::GetDeltaTime()
    {
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        return mSDL2TimerImpl.GetDeltaTime();
#else
#error "Unknown platform Timer"
#endif
    }
}