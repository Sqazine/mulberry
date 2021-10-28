#pragma once
#include "Component.h"
#include "../../Math/Vec2.h"
#include "../../Math/Mat4.h"
struct Transform
{
    Vec2 position;
    float rotation;
    Vec2 scale;
};

class TransformComponent : public Component
{
    COMPONENT_DECLARATION()
public:
    TransformComponent(int updateOrder = 10);
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

    Mat4 GetTransformMatrix() const;
private:
    Transform m_Transform;
};
