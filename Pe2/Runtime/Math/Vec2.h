#pragma once
#include "Math.h"

class Vec2
{
public:
	float x, y;

	Vec2();
	Vec2(float x, float y);
	Vec2(float value);

	friend Vec2 operator+(const Vec2& left, const Vec2& right);
	friend Vec2 operator-(const Vec2& left, const Vec2& right);
	friend Vec2 operator-(const Vec2& right);
	friend Vec2 operator*(const Vec2& left, float value);
	friend Vec2 operator*(float value, const Vec2& right);
	friend float operator*(const Vec2& left, const Vec2& right);

	Vec2& operator+=(float value);
	Vec2& operator+=(const Vec2& right);
	Vec2& operator-=(float value);
	Vec2& operator-=(const Vec2& right);
	Vec2& operator*=(float value);
	Vec2& operator*=(const Vec2& right);
	Vec2& operator/=(float value);
	Vec2& operator=(const Vec2& right);

	//向量长度的平方
	float SquareLength() const;
	//向量长度
	float Length() const;

	//向量点积
	static float Dot(const Vec2& left, const Vec2& right);
	//向量归一化
	static Vec2 Normalize(const Vec2& vec);
	//两个向量之间的夹角
	static float IncludedAngle(const Vec2& left, const Vec2& right);

	static Vec2 Transform(const Vec2& vec, float radian);

	static const Vec2 ZERO;
	static const Vec2 UNITX;
	static const Vec2 UNITY;
};