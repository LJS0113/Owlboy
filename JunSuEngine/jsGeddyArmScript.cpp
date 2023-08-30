#include "jsGeddyArmScript.h"
#include "jsGeddyScript.h"
#include "jsMeshRenderer.h"
#include "jsGameObject.h"
#include "jsResources.h"
#include "jsAnimator.h"
#include "jsGeddyArm.h"
#include "jsObject.h"
#include "jsPlayer.h"
#include "jsPlayerScript.h"
#include "jsInput.h"
#include "jsRigidBody.h"
#include "jsGeddy.h"

namespace js
{
	GeddyArmScript::GeddyArmScript()
	{
	}

	GeddyArmScript::~GeddyArmScript()
	{

	}

	void GeddyArmScript::Initialize()
	{
		//MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		mAnimator = GetOwner()->AddComponent<Animator>();
		cd = GetOwner()->GetComponent<Collider2D>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 geddyPos = tr->GetPosition();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GeddyArmSprite", L"..\\Resources\\Texture\\mechanic_arm.png");
		mAnimator->Create(L"GeddyArmIdleRight", atlas, Vector2(0.0f, 64.0f * 0), Vector2(48.0f, 64.0f), 1);
		mAnimator->Create(L"GeddyArmAttackRight", atlas, Vector2(0.0f, 64.0f * 0), Vector2(48.0f, 64.0f), 5);

		mAnimator->Create(L"GeddyArmIdleLeft", atlas, Vector2(192.0f, 128.0f * 0), Vector2(-48.0f, 128.0f), 1);
		mAnimator->Create(L"GeddyArmAttackLeft", atlas, Vector2(192.0f, 128.0f * 0), Vector2(-48.0f, 128.0f), 5);

		//cd->SetSize(Vector2(0.1f, 0.25f));
		//cd->SetCenter(Vector2(1.7f, 2.0f));

		mAnimator->PlayAnimation(L"GeddyArmIdleRight", true);
		mState = eGeddyArmState::Idle;
	}

	void GeddyArmScript::Update()
	{


		switch (mState)
		{
		case js::GeddyArmScript::eGeddyArmState::Idle:
			idle();
			break;
		case js::GeddyArmScript::eGeddyArmState::Attack:
			attack();
			break;
		default:
			break;
		}
	}


	void GeddyArmScript::idle()
	{
		Transform* armTr = GetOwner()->GetComponent<Transform>();
		Vector3 armPos = armTr->GetPosition();
		Transform* geddyTr = gGeddy->GetComponent<Transform>();
		Vector3 geddyPos = geddyTr->GetPosition();

		armPos = geddyPos;
		armPos.z -= -0.01f;
		armTr->SetPosition(armPos);

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mState = eGeddyArmState::Attack;
		}

	}

	void GeddyArmScript::attack()
	{


		mState = eGeddyArmState::Idle;
	}

	void GeddyArmScript::OnCollisionEnter(Collider2D* other)
	{
	}

	void GeddyArmScript::OnCollisionStay(Collider2D* other)
	{
	}

	void GeddyArmScript::OnCollisionExit(Collider2D* other)
	{
	}

}