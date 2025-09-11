#include "pch.h"
#include "TransformComponent.h"
#include <assert.h>

void TransformComponent::SetTranslation(float x, float y)
{
	LocalDirty = true;
	translation.x = x; translation.y = y;
	MarkWorldDirty();
}

void TransformComponent::SetRotation(float InRotation)
{
	LocalDirty = true;  rotation = InRotation;
	MarkWorldDirty();
}

void TransformComponent::SetScale(float scaleX, float scaleY)
{
	LocalDirty = true;  scale.width = scaleX; scale.height = scaleY;
	MarkWorldDirty();
}

// ������� ������ �����ϸ鼭 ������ �Ұ�
const D2D1::Matrix3x2F& TransformComponent::GetLocalMatrix()
{
	if (LocalDirty)
	{
		//     CachedLocal = D2D1::Matrix3x2F::Scale(Scale.x, Scale.y) *
		//        D2D1::Matrix3x2F::Rotation(Rotation) *
		//       D2D1::Matrix3x2F::Translation(Translation.x, Translation.y);        
		MakeLocalMatrix();
		LocalDirty = false;
	}
	return CachedLocal;
}

// ������� ������ �����ϸ鼭 ������ �Ұ�
const D2D1::Matrix3x2F& TransformComponent::GetWorldMatrix()
{
	if (WorldDirty || LocalDirty)
	{
		CachedWorld = Parent ? GetLocalMatrix() * Parent->GetWorldMatrix() : GetLocalMatrix();
		WorldDirty = false;
	}
	return CachedWorld;
}

void TransformComponent::SetParent(TransformComponent* Target)
{
	if (Target == this) // �ڱ� �ڽ��� �θ�� �����ϴ� ���� ��ȿ
		return;

	if (Parent == Target) // �̹� ������ ����
		return;

	if (Parent != nullptr) // �̹� �θ� ������ �θ𿡼� ����
		Parent->RemoveChild(this);

	Parent = Target; // �θ� �ٲ����.

	if (Parent != nullptr)
		Parent->AddChild(this);	//�θ� ������ �߰�

	// �θ� �������ų� ���� �������� �ڽĿ��� World�ٲٶ�� ����
	MarkWorldDirty();
}

void TransformComponent::Reset()
{
	scale = { 1.0f, 1.0f };
	rotation = { 0.0f };
	translation = { 0.0f, 0.0f };
	LocalDirty = true;
	MarkWorldDirty();
}

void TransformComponent::AddTranslation(float x, float y)
{
	LocalDirty = true;
	translation.x += x;
	translation.y += y;

	MarkWorldDirty();
}

void TransformComponent::AddRotation(float degree)
{
	LocalDirty = true;
	rotation += degree;

	MarkWorldDirty();
}

void TransformComponent::AddScale(float x, float y)
{
	LocalDirty = true;
	scale.width += x;
	scale.height += y;

	MarkWorldDirty();
}

void TransformComponent::MakeLocalMatrix()
{
	float s = sinf(rotation * DEG2RAD);
	float c = cosf(rotation * DEG2RAD);

	CachedLocal = D2D1::Matrix3x2F(
		c * scale.width, -s * scale.height,
		s * scale.width, c * scale.height,
		translation.x, translation.y
	);
}

void TransformComponent::AddChild(TransformComponent* target)
{
	Children.push_back(target);
}

void TransformComponent::RemoveChild(TransformComponent* target)
{
	for (auto it = Children.begin(); it != Children.end(); )
	{
		if (*it == target)
		{
			it = Children.erase(it);
			target->Parent = nullptr; // �ڽ� ���忡���� �θ� ����
			return;
		}
		else
		{
			++it;
		}
	}
}

void TransformComponent::MarkWorldDirty()
{
	WorldDirty = true;

	if (Children.size() <= 0) return;

	for (auto it = Children.begin(); it != Children.end(); ++it)
	{
		(*it)->MarkWorldDirty();
	}
}
