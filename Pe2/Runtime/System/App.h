#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "../Math/Vec2.h"
enum class AppState
{
	INIT,
	PROCESS_INPUT,
	UPDATE,
	DRAW,
	EXIT
};

class App
{
public:
	static void Run();

	static void AddScene(const Scene& scene);
private:
	static void Init();
	static void ProcessInput();
	static void Update();
	static void Draw();
	static void CleanUp();

	static AppState m_State;
};