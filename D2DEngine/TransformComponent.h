#pragma once
#include "Component.h"
#include <d2d1_1.h>

constexpr float DEG2RAD = 3.14159265f / 180.0f;
constexpr float RAD2DEG = 180.0f / 3.14159265f;

class TransformComponent :
	public Component
{
private:
    D2D1_SIZE_F scale;
    float rotation;

public:
    D2D1_POINT_2F translation;
    bool LocalDirty = true;
    bool WorldDirty = true;
    D2D1::Matrix3x2F CachedLocal;
    D2D1::Matrix3x2F CachedWorld;
    TransformComponent* Parent = nullptr;
    std::vector<TransformComponent*> Children;

    TransformComponent(
        float x = 0.0f, float y = 0.0f,
        float sx = 1.0f, float sy = 1.0f,
        float rot = 0.0f)
        : translation(D2D1::Point2F(x,y)),
        scale(D2D1::SizeF(sx, sy)),
        rotation(rot){}

    ~TransformComponent()
    {
        if (Parent)
        {
            Parent->RemoveChild(this);
            Parent = nullptr;
        }
        for (auto child : Children)
        {
            if (child)
                child->Parent = nullptr;
        }
        Children.clear();
    }

    virtual void OnEnable() override {}
    virtual void OnDestroy() override{}

    D2D1_POINT_2F GetTranslation() { return translation; }
    void SetTranslation(float x, float y);
    float GetRotation() { return rotation; }
    void  SetRotation(float InRotation);
    D2D1_SIZE_F GetScale() { return scale; }
    void SetScale(float scaleX, float scaleY);

    // 행렬로 변환
    D2D1::Matrix3x2F ToMatrix()
    {
        return D2D1::Matrix3x2F::Scale(scale.width, scale.height) *
            D2D1::Matrix3x2F::Rotation(rotation) *
            D2D1::Matrix3x2F::Translation(translation.x, translation.y);
    }

    // 복사없이 참조로 리턴하면서 수정은 불가
    const D2D1::Matrix3x2F& GetLocalMatrix();
    // 복사없이 참조로 리턴하면서 수정은 불가
    const D2D1::Matrix3x2F& GetWorldMatrix();
    void SetParent(TransformComponent* parent);
    void Reset();

    void AddTranslation(float x, float y);
    void AddRotation(float degree);
    void AddScale(float x, float y);

    void MakeLocalMatrix();
    void AddChild(TransformComponent* target);
    void RemoveChild(TransformComponent* target);
    void MarkWorldDirty();
};
