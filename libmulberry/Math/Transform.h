#pragma once
#include "Vec2.h"
namespace mulberry
{
    struct Transform
    {
        Vec2 position = Vec2::ZERO;
        float rotation = 0.0f;
        Vec2 scale = Vec2(1.0f);

        bool operator==(const Transform &transform)
        {
            return position == transform.position && rotation == transform.rotation && scale == transform.scale;
        }

        bool operator!=(const Transform &transform)
        {
            return !(*this == transform);
        }

        Transform &operator=(const Transform &transform)
        {
            position = transform.position;
            rotation = transform.rotation;
            scale = transform.scale;
            return *this;
        }

        Mat4 ToMat4() const
        {
            Mat4 model = Mat4();
            model *= Mat4::Translate(position);
            model *= Mat4::Rotate(MathUtils::ToRadian(rotation));
            model *= Mat4::Scale(scale);
            return model;
        }
    };
}