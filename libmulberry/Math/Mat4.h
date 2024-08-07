#pragma once
#include <array>
namespace mulberry
{
    class Vec2;
    class Mat4
    {
    public:
        union
        {
            struct
            {
                float e00, e10, e20, e30, e01, e11, e21, e31, e02, e12, e22, e32, e03, e13, e23, e33;
            };
           std::array<float,16> elements;
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
        Mat4 &operator=(const Mat4 &right);

        static Mat4 Translate(const Vec2 &position);
        static Mat4 Rotate(float radian);
        static Mat4 Scale(float factor);
        static Mat4 Scale(const Vec2 &factor);

        static Mat4 Ortho(float left, float right, float top, float bottom, float znear, float zfar);

        static Mat4 LookAt(const Vec2 &position, float rotRadian = 0);

        static const Mat4 Identity;
    };
}