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
    Color(float r, float g, float b, float a=1.0f);

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

    static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color LightYellow;
	static const Color LightBlue;
	static const Color LightPink;
	static const Color LightGreen;
    static const Color Transparent;
};