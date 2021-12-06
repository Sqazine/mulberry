#pragma once
#include <xmmintrin.h>
class Vec2;
class Mat4
{
public:
    union
    {
        float e00, e10, e20, e30, e01, e11, e21, e31, e02, e12, e22, e32, e03, e13, e23, e33;
        float elements[16];
    };

    Mat4();
    Mat4(float value);

    friend Mat4 operator+(const Mat4 &left, const Mat4 &right);
    friend Mat4 operator-(const Mat4 &left, const Mat4 &right);
    friend Mat4 operator*(const Mat4 &left, const Mat4 &right);
    friend Mat4 operator/(const Mat4 &left, float value);

    friend Mat4 operator*(float value, const Mat4 &right);
    friend Mat4 operator*(const Mat4 &left, float value);

    friend bool operator==(const Mat4 &left, const Mat4 &right);

    Mat4 &operator+=(const Mat4 &right);
    Mat4 &operator-=(const Mat4 &right);
    Mat4 &operator*=(const Mat4 &right);
    Mat4 &operator*=(float value);

    static Mat4 Translate(const Vec2 &position);
    static Mat4 Rotate(float radian);
    static Mat4 Scale(float factor);
    static Mat4 Scale(const Vec2 &factor);

    static Mat4 GLOrthoGraphic(float left, float right, float top, float bottom, float znear, float zfar);
    static Mat4 GLPe2rspective(float fov, float aspect, float znear, float zfar);

    static Mat4 VkOrthoGraphics(float left, float right, float top, float bottom, float near, float far);
    static Mat4 VkPe2rspective(float fov, float aspect, float near, float far);

    static Mat4 LookAt(const Vec2& position,float rotRadian=0);

    static const Mat4 Identity;
};
