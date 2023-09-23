#include "TimerImpl.h"
#include <SDL2/SDL.h>
namespace mulberry
{
	TimerImpl::TimerImpl()
	{
	}

	TimerImpl::~TimerImpl()
	{
	}

	void TimerImpl::Init()
	{
		mStartTick = SDL_GetTicks();
	}

	void TimerImpl::Update(uint32_t lockFrame)
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

	float TimerImpl::GetDeltaTime()
	{
		return mDeltaTime;
	}

}