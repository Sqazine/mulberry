#pragma once

struct Color
{
    union
    {
        struct
        {
            float r, g, b, a;
        };
        float values[4];
    };
    Color();
    Color(float r, float g, float b, float a);

    friend Color operator+(const Color &left, const Color &right);
    friend Color operator+(const Color &left, float value);
    friend Color operator+(float value, const Color &right);
    friend Color operator-(const Color &left, const Color &right);
    friend Color operator-(const Color &left, float value);
    friend Color operator-(float value, const Color &right);
    friend Color operator*(const Color &left, float value);
    friend Color operator*(float value, const Color &right);
    friend Color operator*(const Color &left, const Color &right);

    Color &operator+=(float value);
    Color &operator+=(const Color &right);
    Color &operator-=(float value);
    Color &operator-=(const Color &right);
    Color &operator*=(float value);
    Color &operator*=(const Color &right);
    Color &operator=(const Color &right);

    static const Color BLACK;
};