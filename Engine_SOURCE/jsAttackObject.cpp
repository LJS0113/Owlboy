#include "jsAttackObject.h"
#include "jsTransform.h"
#include "jsCollider2D.h"


namespace js
{
	AttackObject::AttackObject()
	{
		cd = AddComponent<Collider2D>();
		cd->SetSize(Vector2(0.7f, 0.2f));
		cd->SetCenter(Vector2(-0.1f, -0.2f));
	}
	AttackObject::~AttackObject()
	{
	}
	void AttackObject::Initialize()
	{
	}
	void AttackObject::Update()
	{
		GameObject::Update();

	}
	void AttackObject::Render()
	{
		GameObject::Render();

	}
	void AttackObject::LateUpdate()
	{
		GameObject::LateUpdate();

	}
}