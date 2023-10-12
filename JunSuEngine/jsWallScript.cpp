#include "jsWallScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsPlayerScript.h"

namespace js
{
	WallScript::WallScript()
	{
	}
	WallScript::~WallScript()
	{
	}
	void WallScript::Initialize()
	{
	}
	void WallScript::Update()
	{
	}
	void WallScript::LateUpdate()
	{
	}
	void WallScript::Render()
	{
	}
	void WallScript::OnCollisionEnter(Collider2D* other)
	{
		float speed = other->GetOwner()->GetComponent<PlayerScript>()->GetSpeed();
	}
	void WallScript::OnCollisionStay(Collider2D* other)
	{
		other->GetOwner()->GetComponent<PlayerScript>()->SetSpeed(0.0f);
	}
	void WallScript::OnCollisionExit(Collider2D* other)
	{
		other->GetOwner()->GetComponent<PlayerScript>()->SetSpeed(3.0f);
	}
}