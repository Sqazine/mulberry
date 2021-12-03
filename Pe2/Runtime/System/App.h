#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "../Math/Vec2.h"
#include "../Scene/Scene.h"

namespace Pe2
{

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

		static void CreateEmptyScene(std::string_view name);
		static void AddScene(Scene *scene);
		static void RemoveScene(std::string_view name);

	private:
		static void Init();
		static void ProcessInput();
		static void Update();
		static void Draw();
		static void CleanUp();

		static AppState m_State;

		static std::vector<std::unique_ptr<Scene>> m_Scenes;
	};
}