#include "Timer.h"
#include <SDL2/SDL.h>
namespace mulberry
{
	SDL2Timer::SDL2Timer()
	{
	}

	void SDL2Timer::Init()
	{
		mStartTick = SDL_GetTicks();
	}

	void SDL2Timer::Update(uint32_t lockFrame)
	{
		mCurTick = SDL_GetTicks();
		if (lockFrame > 0)
			while (!SDL_TICKS_PASSED(SDL_GetTicks(), mCurTick + (1.0f / lockFrame) * 1000))
				;
		mDeltaTime = (mCurTick - mLastTick) / 1000.0f;
		mLastTick = mCurTick;
		if (mDeltaTime > 0.05f)
			mDeltaTime = 0.05f;
	}

	float SDL2Timer::GetDeltaTime()
	{
		return mDeltaTime;
	}

}