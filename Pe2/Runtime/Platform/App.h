#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "../Math/Vec2.h"
#include "Window.h"
enum class AppState
{
	INIT,
	PROCESS_INPUT,
	UPDATE,
	DRAW,
	EXIT
};
struct AppCreateInfo
{
	WindowInfo windowInfo;
};
class App
{
public:
	App(const AppCreateInfo &info);
	virtual ~App();

	void Run();
private:
	virtual void Init();
	virtual void ProcessInput();
	virtual void Update();
	virtual void Draw();
	virtual void CleanUp();

	AppCreateInfo m_CreateInfo;

	AppState m_State;
};