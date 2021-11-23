#pragma once

struct Color3
{
    union
    {
        struct
        {
            float r, g, b;
        };
        float values[3];
    };

    Color3();
    Color3(float r, float g, float b);

    friend Color3 operator+(const Color3 &left, const Color3 &right);
    friend Color3 operator+(const Color3 &left, float value);
    friend Color3 operator+(float value, const Color3 &right);
    friend Color3 operator-(const Color3 &left, const Color3 &right);
    friend Color3 operator-(const Color3 &left, float value);
    friend Color3 operator-(float value, const Color3 &right);
    friend Color3 operator*(const Color3 &left, float value);
    friend Color3 operator*(float value, const Color3 &right);
    friend Color3 operator*(const Color3 &left, const Color3 &right);

    Color3 &operator+=(float value);
    Color3 &operator+=(const Color3 &right);
    Color3 &operator-=(float value);
    Color3 &operator-=(const Color3 &right);
    Color3 &operator*=(float value);
    Color3 &operator*=(const Color3 &right);
    Color3 &operator=(const Color3 &right);

    static const Color3 BLACK;
};

struct Color4
{
    union
    {
        struct
        {
            float r, g, b, a;
        };
        float values[4];
    };
    Color4();
    Color4(float r, float g, float b, float a);
    Color4(const Color3 &rgb, float a);

    friend Color4 operator+(const Color4 &left, const Color4 &right);
    friend Color4 operator+(const Color4 &left, float value);
    friend Color4 operator+(float value, const Color4 &right);
    friend Color4 operator-(const Color4 &left, const Color4 &right);
    friend Color4 operator-(const Color4 &left, float value);
    friend Color4 operator-(float value, const Color4 &right);
    friend Color4 operator*(const Color4 &left, float value);
    friend Color4 operator*(float value, const Color4 &right);
    friend Color4 operator*(const Color4 &left, const Color4 &right);

    Color4 &operator+=(float value);
    Color4 &operator+=(const Color4 &right);
    Color4 &operator-=(float value);
    Color4 &operator-=(const Color4 &right);
    Color4 &operator*=(float value);
    Color4 &operator*=(const Color4 &right);
    Color4 &operator=(const Color4 &right);

    static const Color4 BLACK;
};