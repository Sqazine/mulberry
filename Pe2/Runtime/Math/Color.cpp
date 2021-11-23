#include "Color.h"

const Color3 Color3::BLACK=Color3();

Color3::Color3()
    : r(0.0f), g(0.0f), b(0.0f)
{
}
Color3::Color3(float r, float g, float b)
    : r(r), g(g), b(b)
{
}

Color3 operator+(const Color3 &left, const Color3 &right)
{
    return Color3(left.r + right.r, left.g + right.g, left.b + right.b);
}

Color3 operator+(const Color3 &left, float value)
{
    return Color3(left.r + value, left.g + value, left.b + value);
}
Color3 operator+(float value, const Color3 &right)
{
    return right + value;
}

Color3 operator-(const Color3 &left, const Color3 &right)
{
    return Color3(left.r - right.r, left.g - right.g, left.b - right.b);
}

Color3 operator-(const Color3 &left, float value)
{
    return Color3(left.r - value, left.g - value, left.b - value);
}
Color3 operator-(float value, const Color3 &right)
{
    return right - value;
}

Color3 operator*(const Color3 &left, float value)
{
    return Color3(left.r * value, left.g * value, left.b * value);
}
Color3 operator*(float value, const Color3 &right)
{
    return right * value;
}
Color3 operator*(const Color3 &left, const Color3 &right)
{
    return Color3(left.r * right.r, left.g * right.g, left.b * right.b);
}

Color3 &Color3::operator+=(float value)
{
    *this = *this + value;
    return *this;
}
Color3 &Color3::operator+=(const Color3 &right)
{
    *this = *this + right;
    return *this;
}
Color3 &Color3::operator-=(float value)
{
    *this = *this - value;
    return *this;
}
Color3 &Color3::operator-=(const Color3 &right)
{
    *this = *this - right;
    return *this;
}
Color3 &Color3::operator*=(float value)
{
    *this = *this * value;
    return *this;
}
Color3 &Color3::operator*=(const Color3 &right)
{
    *this = *this + right;
    return *this;
}
Color3 &Color3::operator=(const Color3 &right)
{
    r = right.r;
    g = right.g;
    b = right.b;

    return *this;
}

const Color4 Color4::BLACK=Color4(Color3(),1.0f);

Color4::Color4()
    : r(0.0f), g(0.0f), b(0.0f), a(1.0f)
{
}
Color4::Color4(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a)
{
}

Color4::Color4(const Color3 &rgb, float a)
    : r(rgb.r), g(rgb.g), b(rgb.b), a(a)
{
}

Color4 operator+(const Color4 &left, const Color4 &right)
{
    return Color4(left.r + right.r, left.g + right.g, left.b + right.b, left.a + right.a);
}

Color4 operator+(const Color4 &left, float value)
{
    return Color4(left.r + value, left.g + value, left.b + value, left.a + value);
}
Color4 operator+(float value, const Color4 &right)
{
    return right + value;
}

Color4 operator-(const Color4 &left, const Color4 &right)
{
    return Color4(left.r - right.r, left.g - right.g, left.b - right.b, left.a - right.a);
}

Color4 operator-(const Color4 &left, float value)
{
    return Color4(left.r - value, left.g - value, left.b - value, left.a - value);
}
Color4 operator-(float value, const Color4 &right)
{
    return right - value;
}

Color4 operator*(const Color4 &left, float value)
{
    return Color4(left.r * value, left.g * value, left.b * value, left.a * value);
}
Color4 operator*(float value, const Color4 &right)
{
    return right * value;
}
Color4 operator*(const Color4 &left, const Color4 &right)
{
    return Color4(left.r * right.r, left.g * right.g, left.b * right.b, left.a * right.a);
}

Color4 &Color4::operator+=(float value)
{
    *this = *this + value;
    return *this;
}
Color4 &Color4::operator+=(const Color4 &right)
{
    *this = *this + right;
    return *this;
}
Color4 &Color4::operator-=(float value)
{
    *this = *this - value;
    return *this;
}
Color4 &Color4::operator-=(const Color4 &right)
{
    *this = *this - right;
    return *this;
}
Color4 &Color4::operator*=(float value)
{
    *this = *this * value;
    return *this;
}
Color4 &Color4::operator*=(const Color4 &right)
{
    *this = *this + right;
    return *this;
}
Color4 &Color4::operator=(const Color4 &right)
{
    r = right.r;
    g = right.g;
    b = right.b;
    a = right.a;

    return *this;
}