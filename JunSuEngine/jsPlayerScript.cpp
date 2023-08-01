#include "jsPlayerScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"
#include "jsTexture.h"
#include "jsResources.h"
#include "jsAnimator.h"
#include "jsMeshRenderer.h"
#include "jsRigidBody.h"
#include "jsCollider2D.h"
#include "jsRenderer.h"

namespace js
{
	PlayerScript::PlayerScript()
		: mState(ePlayerState::None)
		, mbFly(false)
		, mAnimator(nullptr)
		, mbRight(true)
		, cb(nullptr)
		, reverseCB{}
	{
		reverseCB.reverse = 0;

		cb = renderer::constantBuffer[(UINT)eCBType::Reverse];
		cb->SetData(&reverseCB);
		cb->Bind(eShaderStage::PS);
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		mAnimator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"OtusSprite", L"..\\Resources\\Texture\\Otus\\Player_Otus.png");
		mAnimator->Create(L"OtusIdleRight", atlas, Vector2(0.0f, 96.689f * 0), Vector2(112.0f, 96.689f), 3);
		mAnimator->Create(L"OtusMoveRight", atlas, Vector2(0.0f, 96.689f * 1), Vector2(112.0f, 96.689f), 12);
		mAnimator->Create(L"OtusFlyRight", atlas, Vector2(0.0f, 96.689f * 2), Vector2(112.0f, 96.689f), 6);
		mAnimator->Create(L"OtusFallRight", atlas, Vector2(0.0f, 96.689f * 3), Vector2(112.0f, 96.689f), 3);
		mAnimator->Create(L"OtusJumpRight", atlas, Vector2(0.0f, 96.689f * 4), Vector2(112.0f, 96.689f), 3);
		mAnimator->Create(L"OtusJumpFallRight", atlas, Vector2(0.0f, 96.689f * 5), Vector2(112.0f, 96.689f), 5);
		mAnimator->Create(L"OtusHangRight", atlas, Vector2(0.0f, 96.689f * 6), Vector2(112.0f, 96.689f), 9);
		mAnimator->Create(L"OtusBed", atlas, Vector2(0.0f, 96.689f * 13), Vector2(112.0f, 96.689f), 14);
		mAnimator->Create(L"OtusHitRight", atlas, Vector2(0.0f, 96.689f * 14), Vector2(112.0f, 96.689f), 6);
		mAnimator->Create(L"OtusAttackRight", atlas, Vector2(0.0f, 96.689f * 19), Vector2(112.0f, 96.689f), 5);
		mAnimator->Create(L"OtusDeadRight", atlas, Vector2(0.0f, 96.689f * 24), Vector2(112.0f, 96.689f), 12);
		
		mAnimator->Create(L"OtusIdleLeft", atlas, Vector2(1456.0f, 96.689f * 0), Vector2(-112.0f, 96.689f), 3);
		mAnimator->Create(L"OtusMoveLeft", atlas, Vector2(1456.0f, 96.689f * 1), Vector2(-112.0f, 96.689f), 12);
		mAnimator->Create(L"OtusFlyLeft", atlas, Vector2(1456.0f, 96.689f * 2), Vector2(-112.0f, 96.689f), 6);
		mAnimator->Create(L"OtusFallLeft", atlas, Vector2(1456.0f, 96.689f * 3), Vector2(-112.0f, 96.689f), 3);
		mAnimator->Create(L"OtusJumpLeft", atlas, Vector2(1456.0f, 96.689f * 4), Vector2(-112.0f, 96.689f), 3);
		mAnimator->Create(L"OtusJumpFallLeft", atlas, Vector2(1456.0f, 96.689f * 5), Vector2(-112.0f, 96.689f), 5);
		mAnimator->Create(L"OtusHangLeft", atlas, Vector2(1456.0f, 96.689f * 6), Vector2(-112.0f, 96.689f), 9);
		mAnimator->Create(L"OtusHitLeft", atlas, Vector2(1456.0f, 96.689f * 14), Vector2(-112.0f, 96.689f), 6);
		mAnimator->Create(L"OtusAttackLeft", atlas, Vector2(1456.0f, 96.689f * 19), Vector2(-112.0f, 96.689f), 5);
		mAnimator->Create(L"OtusDeadLeft", atlas, Vector2(1456.0f, 96.689f * 24), Vector2(-112.0f, 96.689f), 12);
	
		mAnimator->PlayAnimation(L"OtusIdleRight", true);
		mState = ePlayerState::Idle;
	}

	void PlayerScript::Update()
	{
		if (mbRight)
		{
			// 오른쪽이면 0, 왼쪽이면 1
			reverseCB.reverse = 0;

			cb = renderer::constantBuffer[(UINT)eCBType::Reverse];
			cb->SetData(&reverseCB);
			cb->Bind(eShaderStage::PS);
		}
		else
		{
			// 오른쪽이면 0, 왼쪽이면 1
			reverseCB.reverse = 1;

			cb = renderer::constantBuffer[(UINT)eCBType::Reverse];
			cb->SetData(&reverseCB);
			cb->Bind(eShaderStage::PS);
		}
		switch (mState)
		{
		case js::PlayerScript::ePlayerState::Idle:
			idle();
			break;
		case js::PlayerScript::ePlayerState::Move:
			move();
			break;
		case js::PlayerScript::ePlayerState::Attack:
			attack();
			break;
		case js::PlayerScript::ePlayerState::Death:
			death();
			break;
		case js::PlayerScript::ePlayerState::Dash:
			dash();
			break;
		case js::PlayerScript::ePlayerState::Jump:
			jump();
			break;
		case js::PlayerScript::ePlayerState::Fly:
			fly();
			break;
		default:
			break;
		}

	}

	void PlayerScript::Complete()
	{
		int a = 0;
	}


	void PlayerScript::move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::LEFT))
		{

			pos.x -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			mState = ePlayerState::Move;
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{

			pos.x += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			mState = ePlayerState::Move;
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			//mState = ePlayerState::Move;
		}

		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);

		}

		if (Input::GetKeyUp(eKeyCode::UP)
			|| Input::GetKeyUp(eKeyCode::DOWN)
			|| Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT))
		{
			if (!mbFly)
			{
				if(mbRight)
					mAnimator->PlayAnimation(L"OtusIdleRight", true);
				else
					mAnimator->PlayAnimation(L"OtusIdleLeft", true);
			}
			if (mbFly)
			{
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusFlyRight", true);
				else
					mAnimator->PlayAnimation(L"OtusFlyLeft", true);
			}
			mState = ePlayerState::Idle;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mState = ePlayerState::Attack;
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			mAnimator->PlayAnimation(L"OtusDashRight", false);
			mState = ePlayerState::Dash;
		}

	}

	void PlayerScript::idle()
	{
		//Animator* at = GetOwner()->GetComponent<Animator>();
		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			mAnimator->PlayAnimation(L"OtusJumpFall", true);
			mState = ePlayerState::Move;
			mbFly = false;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mbRight = false;
			if (mbFly)
				mAnimator->PlayAnimation(L"OtusFlyLeft", true);
			else
				mAnimator->PlayAnimation(L"OtusMoveLeft", true);
			mState = ePlayerState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mbRight = true;
			if (mbFly)
				mAnimator->PlayAnimation(L"OtusFlyRight", true);
			else
				mAnimator->PlayAnimation(L"OtusMoveRight", true);
			mState = ePlayerState::Move;
		}


		if (Input::GetKeyDown(eKeyCode::UP))
		{
			if(mbRight)
				mAnimator->PlayAnimation(L"OtusFlyRight", true);
			else
				mAnimator->PlayAnimation(L"OtusFlyLeft", true);
			mbFly = true;
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if(mbRight)
				mAnimator->PlayAnimation(L"OtusAttackRight", false);
			else
				mAnimator->PlayAnimation(L"OtusAttackLeft", false);
			mState = ePlayerState::Attack;
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			
			if (mbRight)
				mAnimator->PlayAnimation(L"OtusDashRight", false);
			else
				mAnimator->PlayAnimation(L"OtusDashLeft", false);
			mState = ePlayerState::Dash;
		}
	}

	void PlayerScript::dash()
	{
		if (Input::GetKeyUp(eKeyCode::SPACE))
		{
			mAnimator->PlayAnimation(L"OtusIdleRight", true);
			mState = ePlayerState::Idle;
		}
	}

	void PlayerScript::jump()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::UP))
		{
			mAnimator->PlayAnimation(L"OtusFlyRight", true);
			mState = ePlayerState::Fly;
		}

		if (Input::GetKeyUp(eKeyCode::UP))
		{
			if (!mbFly)
				mState = ePlayerState::Idle;

		}
	}

	void PlayerScript::attack()
	{
		if (Input::GetKeyUp(eKeyCode::LBUTTON))
		{
			if(mbRight)
				mAnimator->PlayAnimation(L"OtusIdleRight", true);
			else
				mAnimator->PlayAnimation(L"OtusIdleLeft", true);
			mState = ePlayerState::Idle;
		}

	}

	void PlayerScript::death()
	{
	}

	void PlayerScript::fly()
	{
		if (Input::GetKeyUp(eKeyCode::UP))
		{
			mAnimator->PlayAnimation(L"OtusIdleRight", true);
			mState = ePlayerState::Idle;
		}
	}

	void PlayerScript::OnCollisionEnter(Collider2D* other)
	{
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Collider2D* cd = GetOwner()->GetComponent<Collider2D>();
		//Rigidbody* rigid = GetOwner()->GetComponent<Rigidbody>();

		//if (other->GetColliderOwner() == eColliderOwner::Ground)
		//{
		//	int a = 0;
		//	rigid->SetGround(true);
		//}
	}
	void PlayerScript::OnCollisionStay(Collider2D* other)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* other)
	{
		//Collider2D* cd = GetOwner()->GetComponent<Collider2D>();
		//Rigidbody* rigid = GetOwner()->GetComponent<Rigidbody>();

		//if (other->GetColliderOwner() == eColliderOwner::Player)
		//{
		//	rigid->SetGround(false);
		//}
	}

}