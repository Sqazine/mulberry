#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include "Math/Vec2.h"
struct WindowCreateInfo
{
	std::string title;
	Vec2 extent;
	bool resizeable = true;
};

struct ApplicationCreateInfo
{
	WindowCreateInfo windowCreateInfo;
};

class Application
{
public:
	Application(const ApplicationCreateInfo &info);
	~Application();

	void Run();
private:
	void Init();
	void ProcessInput();
	void Update();
	void Draw();
	void CleanUp();

	ApplicationCreateInfo m_CreateInfo;

	bool m_IsRunning;

	SDL_Window *m_WindowHandle;
};