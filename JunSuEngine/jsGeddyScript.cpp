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

namespace js
{
	GeddyScript::GeddyScript()
		:mState(eGeddyState::Idle)
		, mbRight(true)
		, mbHang(false)
	{
	}

	GeddyScript::~GeddyScript()
	{
	}

	void GeddyScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		mAnimator = GetOwner()->AddComponent<Animator>();
		cd = GetOwner()->GetComponent<Collider2D>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 geddyPos = tr->GetPosition();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GeddySprite", L"..\\Resources\\Texture\\Geddy.png");
		mAnimator->Create(L"GeddyIdleRight", atlas, Vector2(0.0f, 72.636f * 6), Vector2(64.0f, 72.636f), 13);
		mAnimator->Create(L"GeddyHangRight", atlas, Vector2(0.0f, 72.636f * 1), Vector2(64.0f, 72.636f), 5);
		mAnimator->Create(L"GeddyFallRight", atlas, Vector2(0.0f, 72.636f * 5), Vector2(64.0f, 72.636f), 3);

		mAnimator->Create(L"GeddyIdleLeft", atlas, Vector2(896.0f, 72.636f * 6), Vector2(-64.0f, 72.636f), 13);
		mAnimator->Create(L"GeddyHangLeft", atlas, Vector2(896.0f, 72.636f * 1), Vector2(-64.0f, 72.636f), 5);
		mAnimator->Create(L"GeddyFallLeft", atlas, Vector2(896.0f, 72.636f * 5), Vector2(-64.0f, 72.636f), 3);

		cd->SetSize(Vector2(0.1f, 0.25f));
		cd->SetCenter(Vector2(1.7f, 2.0f));

		mAnimator->PlayAnimation(L"GeddyIdleRight", true);
		mState = eGeddyState::Idle;
	}

	void GeddyScript::Update()
	{
		mbRight = gPlayer->GetComponent<PlayerScript>()->GetRightDir();

		switch (mState)
		{
		case js::GeddyScript::eGeddyState::Idle:
			idle();
			break;
		case js::GeddyScript::eGeddyState::Move:
			move();
			break;
		case js::GeddyScript::eGeddyState::Attack:
			attack();
			break;
		case js::GeddyScript::eGeddyState::Hang:
			hang();
			break;
		case js::GeddyScript::eGeddyState::Death:
			death();
			break;
		case js::GeddyScript::eGeddyState::Fall:
			fall();
			break;
		default:
			break;
		}
	}

	void GeddyScript::OnCollisionEnter(Collider2D* other)
	{
	}

	void GeddyScript::OnCollisionStay(Collider2D* other)
	{
	}

	void GeddyScript::OnCollisionExit(Collider2D* other)
	{
	}

	void GeddyScript::idle()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		if (Input::GetKeyDown(eKeyCode::R))
		{
			mbHang = true;
			rb->SetGround(true);
			if (mbHang)
			{
				if (mbRight)
				{
					mAnimator->PlayAnimation(L"GeddyHangRight", true);
				}
				else
				{
					mAnimator->PlayAnimation(L"GeddyHangLeft", true);
				}
				mState = eGeddyState::Hang;
			}
		}

	}

	void GeddyScript::move()
	{
		Transform* geddyTr = GetOwner()->GetComponent<Transform>();
		Vector3 geddyPos = geddyTr->GetPosition();
		Transform* otusTr = gPlayer->GetComponent<Transform>();
		Vector3 otusPos = otusTr->GetPosition();

		geddyPos = otusPos;
		geddyPos.y -= 0.5f;
		if (mbRight)
		{
			geddyPos.x -= 0.1f;
		}
		else
		{
			geddyPos.x += 0.1f;
		}
		geddyTr->SetPosition(geddyPos);

		mState = eGeddyState::Hang;
	}

	void GeddyScript::attack()
	{
	}

	void GeddyScript::death()
	{
	}

	void GeddyScript::hang()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Transform* geddyTr = GetOwner()->GetComponent<Transform>();
		Vector3 geddyPos = geddyTr->GetPosition();
		Transform* otusTr = gPlayer->GetComponent<Transform>();
		Vector3 otusPos = otusTr->GetPosition();

		geddyPos = otusPos;
		geddyPos.y -= 0.5f;
		if (mbRight)
		{
			geddyPos.x -= 0.1f;
		}
		else
		{
			geddyPos.x += 0.1f;
		}
		geddyTr->SetPosition(geddyPos);

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			if (mbHang)
			{
				mAnimator->PlayAnimation(L"GeddyHangRight", true);
				mState = eGeddyState::Move;
			}
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			if (mbHang)
			{
				mAnimator->PlayAnimation(L"GeddyHangLeft", true);
				mState = eGeddyState::Move;
			}
		}

		if (Input::GetKeyDown(eKeyCode::RBUTTON))
		{
			mbHang = false;
			rb->SetGround(false);
			if(mbRight)
				mAnimator->PlayAnimation(L"GeddyIdleRight", true);
			else
				mAnimator->PlayAnimation(L"GeddyIdleLeft", true);
			mState = eGeddyState::Idle;
		}
	}

	void GeddyScript::fall()
	{
	}

}