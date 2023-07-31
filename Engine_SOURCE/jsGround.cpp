#include "jsGround.h"
#include "jsCollider2D.h"
#include "jsGameObject.h"
#include "jsRigidBody.h"
#include "jsComponent.h"



namespace js
{

	Ground::Ground()
		: mCollider(nullptr)
		, mPlayer(nullptr)
	{
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

	void Ground::OnCollisionEnter(Collider2D* other)
	{


	}

	void Ground::OnCollisionStay(Collider2D* other)
	{
	}

	void Ground::OnCollisionExit(Collider2D* other)
	{

	}

}