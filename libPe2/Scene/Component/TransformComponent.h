#pragma once
#include "Component.h"
#include "../../Math/Vec2.h"
#include "../../Math/Mat4.h"

namespace Pe2
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
    };

    class TransformComponent : public Component
    {
        COMPONENT_DECLARATION()
    public:
        TransformComponent(int32_t updateOrder = 0);
        ~TransformComponent();

        void SetPosition(const Vec2 &pos);
        void SetPosition(float posX, float posY);
        const Vec2 &GetPosition() const;
        void Translate(const Vec2 &pos);

        void SetRotation(float radian);
        float GetRotation() const;
        void Rotate(float radian);

        void SetScale(float scale);
        void SetScale(const Vec2 &scale);
        void SetScale(float scaleX, float scaleY);
        const Vec2 &GetScale() const;

        Vec2 GetLocalAxisX() const;
        Vec2 GetLocalAxisY() const;

        Mat4 GetModelMat() const;

        const Transform &GetTransform() const;

    private:
        Transform m_Transform;
    };
}