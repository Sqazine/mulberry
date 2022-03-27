#include "Vec2.h"

namespace mulberry
{
	const Vec2 Vec2::ZERO = Vec2();
	const Vec2 Vec2::UNIT_X(1.0f, 0.0f);
	const Vec2 Vec2::UNIT_Y(0.0f, 1.0f);

	Vec2::Vec2()
		: x(0.0f), y(0.0f)
	{
	}

	Vec2::Vec2(float x, float y)
		: x(x), y(y)
	{
	}

	Vec2::Vec2(float value)
		: x(value), y(value)
	{
	}

	Vec2 operator+(const Vec2 &left, const Vec2 &right)
	{
		return Vec2(left.x + right.x, left.y + right.y);
	}

	Vec2 operator-(const Vec2 &left, const Vec2 &right)
	{
		return Vec2(left.x - right.x, left.y - right.y);
	}

	Vec2 operator-(const Vec2 &right)
	{
		return Vec2(-right.x, -right.y);
	}

	Vec2 operator*(const Vec2 &left, float value)
	{
		return Vec2(left.x * value, left.y * value);
	}

	Vec2 operator*(float value, const Vec2 &right)
	{
		return right * value;
	}

	Vec2 operator*(const Vec2 &left, const Vec2 &right)
	{
		return Vec2(left.x * right.x, left.y * right.y);
	}

	bool Vec2::operator==(const Vec2 &right)
	{
		return this->x==right.x&&this->y==right.y;
	}

	Vec2 &Vec2::operator+=(float value)
	{
		x += value;
		y += value;
		return *this;
	}

	Vec2 &Vec2::operator+=(const Vec2 &right)
	{

		x += right.x;
		y += right.y;
		return *this;
	}

	Vec2 &Vec2::operator-=(float value)
	{

		x -= value;
		y -= value;
		return *this;
	}

	Vec2 &Vec2::operator-=(const Vec2 &right)
	{

		x -= right.x;
		y -= right.y;
		return *this;
	}

	Vec2 &Vec2::operator*=(float value)
	{

		x *= value;
		y *= value;
		return *this;
	}

	Vec2 &Vec2::operator*=(const Vec2 &right)
	{

		x *= right.x;
		y *= right.y;
		return *this;
	}

	Vec2 &Vec2::operator/=(float value)
	{

		x /= value;
		y /= value;
		return *this;
	}

	Vec2 &Vec2::operator=(const Vec2 &right)
	{

		x = right.x;
		y = right.y;
		return *this;
	}

	float Vec2::Dot(const Vec2 &left, const Vec2 &right)
	{
		return left.x * right.x + left.y * right.y;
	}

	Vec2 Vec2::Normalize(const Vec2 &vec)
	{
		Vec2 tmp = vec;
		float len = tmp.Length();
		if (len > 0)
		{
			tmp.x /= len;
			tmp.y /= len;
		}
		return tmp;
	}

	float Vec2::IncludedAngle(const Vec2 &left, const Vec2 &right)
	{
		Normalize(left);
		Normalize(right);

		return MathUtils::ArcCos(Dot(left, right));
	}

	Vec2 Vec2::Rotate(const Vec2 &vec, float radian)
	{
		return Vec2(MathUtils::Cos(radian) * vec.x - MathUtils::Sin(radian) * vec.y, MathUtils::Sin(radian) * vec.x + MathUtils::Cos(radian) * vec.y);
	}

	Vec2 Vec2::Translate(const Vec2 &vec, const Vec2 &t)
	{
		return vec + t;
	}
	Vec2 Vec2::Scale(const Vec2 &vec, const Vec2 &s)
	{
		return vec * s;
	}

	float Vec2::SquareLength() const
	{
		return x * x + y * y;
	}

	float Vec2::Length() const
	{
		return MathUtils::Sqrt(SquareLength());
	}
}