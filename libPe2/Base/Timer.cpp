#include "Timer.h"
#include <SDL2/SDL.h>

Timer::Timer()
{
}

void Timer::Init()
{
	m_StartTick = SDL_GetTicks();
}

void Timer::Update(uint32_t lockFrame)
{
	m_CurTick = SDL_GetTicks();
	if (lockFrame > 0)
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_CurTick + (1.0f / lockFrame) * 1000))
			;
	m_DeltaTime = (m_CurTick - m_LastTick) / 1000.0f;
	m_LastTick = m_CurTick;
	if (m_DeltaTime > 0.05f)
		m_DeltaTime = 0.05f;
}

float Timer::GetDeltaTime()
{
	return m_DeltaTime;
}
