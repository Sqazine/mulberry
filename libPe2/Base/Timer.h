#pragma once
#include <cstdint>
class Timer
{
public:
	Timer();
	 void Init();
	 void Update(uint32_t lockFrame = 0);

	 float GetDeltaTime();

private:

	 uint32_t m_StartTick;
	 uint32_t m_CurTick;
	 uint32_t m_LastTick;
	 float m_DeltaTime;
};