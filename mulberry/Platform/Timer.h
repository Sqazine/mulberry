#pragma once

namespace mulberry
{
  class Timer
  {
  public:
    Timer() = default;
    virtual ~Timer() = default;
    virtual void Init() = 0;
    virtual void Update(uint32_t lockFrame = 0) = 0;

    virtual float GetDeltaTime() = 0;

    virtual float GetFPS() = 0;
  };
}