#include "jsGround.h"
#include "jsCollider2D.h"
#include "jsGameObject.h"
#include "jsRigidBody.h"
#include "jsComponent.h"
#include "..\JunSuEngine\jsGroundScript.h"

namespace js
{

	Ground::Ground()
	{
		AddComponent<GroundScript>();
		AddComponent<Collider2D>();
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();
	}

	void Ground::Render()
	{
		GameObject::Render();
	}

	void Ground::LateUpdate()
	{
		GameObject::LateUpdate();
	}

}