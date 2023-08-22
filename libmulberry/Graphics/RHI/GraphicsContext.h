#pragma once
#include <memory>
#include <mutex>
#include "Vec2.h"
#include "Core/Singleton.h"
#include "GraphicsConfig.h"
namespace mulberry
{
	class GraphicsContext : public Singleton<GraphicsContext>
	{
	public:
		void Init();
		void Destroy();

		void BeginFrame();
		void EndFrame();
	};
}