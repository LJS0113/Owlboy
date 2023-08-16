#include "jsDoor.h"
#include "jsTransform.h"
#include "jsCollider2D.h"


namespace js
{
	Door::Door()
	{
		AddComponent<Transform>();
		AddComponent<Collider2D>();
		GetComponent<Collider2D>()->SetColliderOwner(eColliderOwner::Door);
	}
	Door::~Door()
	{
	}
	void Door::Initialize()
	{

	}
	void Door::Update()
	{
		GameObject::Update();

	}
	void Door::Render()
	{
		GameObject::Render();

	}
	void Door::LateUpdate()
	{
		GameObject::LateUpdate();

	}
}