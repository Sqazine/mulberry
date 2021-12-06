#include "Mat4.h"
#include <cstdint>
#include "Vec2.h"
const Mat4 Mat4::Identity = Mat4();

Mat4::Mat4()
{
	for (uint8_t i = 0; i < 16; ++i)
		elements[i] = 0;
	elements[0] = elements[5] = elements[10] = elements[15] = 1.0f;
}

Mat4::Mat4(float value)
{
	for (uint8_t i = 0; i < 16; ++i)
		elements[i] = 0;
	elements[0] = elements[5] = elements[10] = elements[15] = value;
}

Mat4 operator+(const Mat4& left, const Mat4& right)
{
	Mat4 tmpMat;
	for (uint8_t i = 0; i < 16; ++i)
		tmpMat.elements[i] = left.elements[i] + right.elements[i];
	return tmpMat;
}

Mat4 operator-(const Mat4& left, const Mat4& right)
{
	Mat4 tmpMat;
	for (uint8_t i = 0; i < 16; ++i)
		tmpMat.elements[i] = left.elements[i] - right.elements[i];
	return tmpMat;
}

Mat4 operator*(const Mat4& left, const Mat4& right)
{
	Mat4 tmpMat;
	tmpMat.elements[0] = left.elements[0] * right.elements[0] + left.elements[4] * right.elements[1] + left.elements[8] * right.elements[2] + left.elements[12] * right.elements[3];
	tmpMat.elements[1] = left.elements[1] * right.elements[0] + left.elements[5] * right.elements[1] + left.elements[9] * right.elements[2] + left.elements[13] * right.elements[3];
	tmpMat.elements[2] = left.elements[2] * right.elements[0] + left.elements[6] * right.elements[1] + left.elements[10] * right.elements[2] + left.elements[14] * right.elements[3];
	tmpMat.elements[3] = left.elements[3] * right.elements[0] + left.elements[7] * right.elements[1] + left.elements[11] * right.elements[2] + left.elements[15] * right.elements[3];

	tmpMat.elements[4] = left.elements[0] * right.elements[4] + left.elements[4] * right.elements[5] + left.elements[8] * right.elements[6] + left.elements[12] * right.elements[7];
	tmpMat.elements[5] = left.elements[1] * right.elements[4] + left.elements[5] * right.elements[5] + left.elements[9] * right.elements[6] + left.elements[13] * right.elements[7];
	tmpMat.elements[6] = left.elements[2] * right.elements[4] + left.elements[6] * right.elements[5] + left.elements[10] * right.elements[6] + left.elements[14] * right.elements[7];
	tmpMat.elements[7] = left.elements[3] * right.elements[4] + left.elements[7] * right.elements[5] + left.elements[11] * right.elements[6] + left.elements[15] * right.elements[7];

	tmpMat.elements[8] = left.elements[0] * right.elements[8] + left.elements[4] * right.elements[9] + left.elements[8] * right.elements[10] + left.elements[12] * right.elements[11];
	tmpMat.elements[9] = left.elements[1] * right.elements[8] + left.elements[5] * right.elements[9] + left.elements[9] * right.elements[10] + left.elements[13] * right.elements[11];
	tmpMat.elements[10] = left.elements[2] * right.elements[8] + left.elements[6] * right.elements[9] + left.elements[10] * right.elements[10] + left.elements[14] * right.elements[11];
	tmpMat.elements[11] = left.elements[3] * right.elements[8] + left.elements[7] * right.elements[9] + left.elements[11] * right.elements[10] + left.elements[15] * right.elements[11];

	tmpMat.elements[12] = left.elements[0] * right.elements[12] + left.elements[4] * right.elements[13] + left.elements[8] * right.elements[14] + left.elements[12] * right.elements[15];
	tmpMat.elements[13] = left.elements[1] * right.elements[12] + left.elements[5] * right.elements[13] + left.elements[9] * right.elements[14] + left.elements[13] * right.elements[15];
	tmpMat.elements[14] = left.elements[2] * right.elements[12] + left.elements[6] * right.elements[13] + left.elements[10] * right.elements[14] + left.elements[14] * right.elements[15];
	tmpMat.elements[15] = left.elements[3] * right.elements[12] + left.elements[7] * right.elements[13] + left.elements[11] * right.elements[14] + left.elements[15] * right.elements[15];

	return tmpMat;
}

Mat4 operator/(const Mat4& left, float value)
{
	Mat4 tmpMat;
	for (uint8_t i = 0; i < 16; ++i)
		tmpMat.elements[i] = left.elements[i] / value;
	return tmpMat;
}

Mat4 operator*(float value, const Mat4& right)
{
	Mat4 tmpMat;
	for (uint8_t i = 0; i < 16; ++i)
		tmpMat.elements[i] = right.elements[i] * value;
	return tmpMat;
}

Mat4 operator*(const Mat4& left, float value)
{
	return value * left;
}

bool operator==(const Mat4& left, const Mat4& right)
{
	for (uint8_t i = 0; i < 16; ++i)
		if (left.elements[i] != right.elements[i])
			return false;
	return true;
}

Mat4& Mat4::operator+=(const Mat4& right)
{
	
	*this = *this + right;
	return *this;
}

Mat4& Mat4::operator-=(const Mat4& right)
{
	
	*this = *this - right;
	return *this;
}

Mat4& Mat4::operator*=(const Mat4& right)
{
	
	*this = *this * right;
	return *this;
}

Mat4& Mat4::operator*=(float value)
{
	
	*this = *this * value;
	return *this;
}

Mat4 Mat4::Translate(const Vec2& position)
{
	Mat4 tmpMat;
	tmpMat.elements[12] = position.x;
	tmpMat.elements[13] = position.y;
	return tmpMat;
}

Mat4 Mat4::Rotate(float radian)
{
	Mat4 tmpMat;
	float radian_cos = MathUtils::Cos(radian);
	float radian_sin = MathUtils::Sin(radian);

    tmpMat.e00=tmpMat.e11=radian_cos;
    tmpMat.e10=radian_sin;
    tmpMat.e01=-radian_sin;

	return tmpMat;
}

Mat4 Mat4::Scale(float factor)
{
	Mat4 tmpMat;
	tmpMat.elements[0] = tmpMat.elements[5] = tmpMat.elements[10] = factor;
	return tmpMat;
}

Mat4 Mat4::Scale(const Vec2& factor)
{
	Mat4 tmpMat;
	tmpMat.elements[0] = factor.x;
	tmpMat.elements[5] = factor.y;
	return tmpMat;
}

Mat4 Mat4::GLOrthoGraphic(float left, float right, float top, float bottom, float znear, float zfar)
{
	Mat4 tmpMat;
	tmpMat.elements[0] = 2 / (right - left);
	tmpMat.elements[5] = 2 / (top - bottom);
	tmpMat.elements[10] = 2 / (znear - zfar);
	tmpMat.elements[12] = (left + right) / (left - right);
	tmpMat.elements[13] = (bottom + top) / (bottom - top);
	tmpMat.elements[14] = (znear + zfar) / (znear - zfar);
	return tmpMat;
}

Mat4 Mat4::GLPe2rspective(float fov, float aspect, float znear, float zfar)
{
	Mat4 tmpMat(0.0f);
	float cotFov = MathUtils::Cot(fov / 2);
	tmpMat.elements[0] = cotFov / aspect;
	tmpMat.elements[5] = cotFov;
	tmpMat.elements[10] = (znear + zfar) / (znear - zfar);
	tmpMat.elements[11] = -1;
	tmpMat.elements[14] = 2 * znear * zfar / (znear - zfar);
	return tmpMat;
}

Mat4 Mat4::LookAt(const Vec2& position,float rotRadian)
{
	Mat4 tmpMat;
	Vec2 axisX = Vec2::Rotate(Vec2::UNITX,rotRadian);
	Vec2 axisY =Vec2::Rotate(Vec2::UNITY,rotRadian+MathUtils::ToRadian(90.0f));

	Mat4 rotPart;
	rotPart.elements[0] = axisX.x;
	rotPart.elements[1] = axisY.x;
	rotPart.elements[2] = 0.0f;

	rotPart.elements[4] = axisX.y;
	rotPart.elements[5] = axisY.y;
	rotPart.elements[6] = 0.0f;

	rotPart.elements[8] = 0;
	rotPart.elements[9] = 0;
	rotPart.elements[10] = 1.0f;

	Mat4 transPart;
	transPart.elements[12] = -position.x;
	transPart.elements[13] = -position.y;

	return rotPart * transPart;
}