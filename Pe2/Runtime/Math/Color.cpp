#include "Color.h"

const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f, 1.0f);

Color::Color()
    : r(0.0f), g(0.0f), b(0.0f), a(1.0f)
{
}
Color::Color(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a)
{
}

Color operator+(const Color &left, const Color &right)
{
    return Color(left.r + right.r, left.g + right.g, left.b + right.b, left.a + right.a);
}

Color operator+(const Color &left, float value)
{
    return Color(left.r + value, left.g + value, left.b + value, left.a + value);
}
Color operator+(float value, const Color &right)
{
    return right + value;
}

Color operator-(const Color &left, const Color &right)
{
    return Color(left.r - right.r, left.g - right.g, left.b - right.b, left.a - right.a);
}

Color operator-(const Color &left, float value)
{
    return Color(left.r - value, left.g - value, left.b - value, left.a - value);
}
Color operator-(float value, const Color &right)
{
    return right - value;
}

Color operator*(const Color &left, float value)
{
    return Color(left.r * value, left.g * value, left.b * value, left.a * value);
}
Color operator*(float value, const Color &right)
{
    return right * value;
}
Color operator*(const Color &left, const Color &right)
{
    return Color(left.r * right.r, left.g * right.g, left.b * right.b, left.a * right.a);
}

Color &Color::operator+=(float value)
{
    *this = *this + value;
    return *this;
}
Color &Color::operator+=(const Color &right)
{
    *this = *this + right;
    return *this;
}
Color &Color::operator-=(float value)
{
    *this = *this - value;
    return *this;
}
Color &Color::operator-=(const Color &right)
{
    *this = *this - right;
    return *this;
}
Color &Color::operator*=(float value)
{
    *this = *this * value;
    return *this;
}
Color &Color::operator*=(const Color &right)
{
    *this = *this + right;
    return *this;
}
Color &Color::operator=(const Color &right)
{
    r = right.r;
    g = right.g;
    b = right.b;
    a = right.a;

    return *this;
}