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

	 uint32_t mStartTick;
	 uint32_t mCurTick;
	 uint32_t mLastTick;
	 float mDeltaTime;
};