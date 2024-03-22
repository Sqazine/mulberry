#pragma once
#include "Component.h"
#include "Vec2.h"
#include "Math/Mat4.h"
#include "Math/Transform.h"
namespace mulberry
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent(int32_t updateOrder = 0);
        ~TransformComponent();

        void SetPosition(const Vec2 &pos);
        void SetPosition(float posX, float posY);
        const Vec2 &GetPosition() const;
        void Translate(const Vec2 &pos);

        void SetRotation(float degree);
        float GetRotation() const;
        void Rotate(float degree);

        void SetScale(float scale);
        void SetScale(const Vec2 &scale);
        void SetScale(float scaleX, float scaleY);
        const Vec2 &GetScale() const;

        Vec2 GetLocalAxisX() const;
        Vec2 GetLocalAxisY() const;

        Mat4 GetModelMat() const;

        const Transform &GetTransform() const;

    private:
        Transform mTransform;
    };
}