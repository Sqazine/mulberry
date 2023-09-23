#pragma once
#include <cstdint>
#include "Platform/Timer.h"
namespace mulberry
{
	class TimerImpl : public Timer
	{
	public:
		TimerImpl();
		~TimerImpl() override;
		void Init() override;
		void Update(uint32_t lockFrame = 0) override;

		float GetDeltaTime() override;

	private:
		uint32_t mStartTick;
		uint32_t mCurTick;
		uint32_t mLastTick;
		float mDeltaTime;
	};
}