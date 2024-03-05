#pragma once
#include "Math/Vec2.h"
namespace mulberry
{
	struct Scissor
	{
		Scissor() : offset(Vec2::ZERO), extent(Vec2::ZERO) {}
		Scissor(const Vec2 &offset, const Vec2 &extent) : offset(offset), extent(extent) {}
		Vec2 offset;
		Vec2 extent;
	};
	
	class Viewport
	{
	public:
		Viewport(float x = 0, float y = 0, float w = 0, float h = 0) : x(x), y(y), width(w), height(h), scissor({x, y}, {width, height}) {}
		~Viewport() {}
		float x, y, width, height;
		Scissor scissor;
	};
}