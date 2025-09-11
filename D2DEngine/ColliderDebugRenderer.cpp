#include "pch.h"
#include "ColliderDebugRenderer.h"
#include "BoxColliderComponent.h"
#include "D2DEngineWrapper.h"

extern bool g_bUnityCoords;
extern D2D1::Matrix3x2F g_matUnity;

void ColliderDebugRenderer::Render()
{
	if (!visible) return;

	auto* tr = owner->GetComponent<TransformComponent>();
	auto* box = owner->GetComponent<BoxColliderComponent>();
	if (!tr || !box) return;

	AABB aabb = box->GetAABB();

	float left = aabb.centerX - aabb.halfW;
	float right = aabb.centerX + aabb.halfW;
	float top = aabb.centerY - aabb.halfH;
	float bottom = aabb.centerY + aabb.halfH;

	auto& d2d = D2DEngineWrapper::GetInstance();

	D2D1::Matrix3x2F matFinal = D2D1::Matrix3x2F::Identity() * g_matUnity;
	
	if (g_bUnityCoords)
		matFinal = D2D1::Matrix3x2F::Identity() * g_matUnity;

	d2d.GetDC()->SetTransform(matFinal);

	d2d.DrawRect(left, top-2, right, bottom-2, D2D1::ColorF::Red);
}
