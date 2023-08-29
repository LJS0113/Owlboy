#include "jsGroundScript.h"
#include "jsGameObject.h"
#include "jsRigidBody.h"

namespace js
{
	GroundScript::GroundScript()
	{
	}
	GroundScript::~GroundScript()
	{
	}
	void GroundScript::Initialize()
	{
	}
	void GroundScript::Update()
	{
	}
	void GroundScript::LateUpdate()
	{
	}
	void GroundScript::Render()
	{
	}
	void GroundScript::OnCollisionEnter(Collider2D* other)
	{
		Transform* grTr = GetOwner()->GetComponent<Transform>();
		Transform* playerTr = other->GetOwner()->GetComponent<Transform>();

		Vector3 grPos = grTr->GetPosition();
		Vector3 playerPos = playerTr->GetPosition();

		playerPos.y = grPos.y + 0.3f;

		playerTr->SetPosition(playerPos);
		other->GetOwner()->GetComponent<Rigidbody>()->SetGround(true);
	}
	void GroundScript::OnCollisionStay(Collider2D* other)
	{

	}
	void GroundScript::OnCollisionExit(Collider2D* other)
	{
		other->GetOwner()->GetComponent<Rigidbody>()->SetGround(false);
	}
}