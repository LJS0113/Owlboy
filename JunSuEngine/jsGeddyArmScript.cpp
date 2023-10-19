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
#include "jsGeddyBullet.h"

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
		mAnimator = GetOwner()->AddComponent<Animator>();
		cd = GetOwner()->GetComponent<Collider2D>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 geddyPos = tr->GetPosition();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GeddyArmSprite", L"..\\Resources\\Texture\\mechanic_arm.png");
		mAnimator->Create(L"GeddyArmIdleRight", atlas, Vector2(0.0f, 64.0f * 0), Vector2(48.0f, 64.0f), 1);
		mAnimator->Create(L"GeddyArmAttackRight", atlas, Vector2(0.0f, 64.0f * 0), Vector2(48.0f, 64.0f), 5);

		mAnimator->Create(L"GeddyArmIdleLeft", atlas, Vector2(192.0f, 128.0f * 0), Vector2(-48.0f, 128.0f), 1);
		mAnimator->Create(L"GeddyArmAttackLeft", atlas, Vector2(192.0f, 128.0f * 0), Vector2(-48.0f, 128.0f), 5);

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
		armPos.y -= 0.1f;
		armPos.z -= 0.1f;
		armTr->SetPosition(armPos);

		Vector2 pos = Input::GetMousePos();
		Vector3 mousePos = Vector3(pos.x, pos.y, 1.0f);
		mousePos = armTr->GetNDCPos(Vector3(mousePos.x, mousePos.y, mousePos.z));

		float rad = atan2(mousePos.x, mousePos.y);
		rad -= XM_PI / 2.0f;

		armTr->SetRotation(Vector3(0.0f, 0.0f, -rad));

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mAnimator->PlayAnimation(L"GeddyArmAttackRight", false);
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