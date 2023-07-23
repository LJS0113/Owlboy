#include "jsPlayerScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"
#include "jsTexture.h"
#include "jsResources.h"
#include "jsAnimator.h"
#include "jsMeshRenderer.h"



namespace js
{
	PlayerScript::PlayerScript()
		: mState(ePlayerState::None)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"OtusSprite", L"..\\Resources\\Texture\\Player_Otus.png");
		mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->Create(L"OtusIdle", atlas, Vector2(0.0f, 0.0f), Vector2(112.0f, 100.0f), 3);
		mAnimator->Create(L"OtusMove", atlas, Vector2(0.0f, 100.0f), Vector2(112.0f, 100.0f), 12);

		mAnimator->PlayAnimation(L"OtusIdle", true);
		mState = ePlayerState::Idle;
	}

	void PlayerScript::Update()
	{
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
			mAnimator->PlayAnimation(L"OtusMove", true);
			pos.x -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			mAnimator->PlayAnimation(L"OtusMove", true);
			pos.x += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			mState = ePlayerState::Jump;
		}

		if (Input::GetKeyUp(eKeyCode::UP)
			|| Input::GetKeyUp(eKeyCode::DOWN)
			|| Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Idle;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mState = ePlayerState::Attack;
		}

	}

	void PlayerScript::idle()
	{
		//Animator* at = GetOwner()->GetComponent<Animator>();
		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::LEFT)
			|| Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::UP))
		{
			pos.y += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			mState = ePlayerState::Jump;
		}
		
		if (Input::GetKeyDown(eKeyCode::UP)
			|| Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::LEFT)
			|| Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mState = ePlayerState::Attack;
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			mState = ePlayerState::Dash;
		}
	}

	void PlayerScript::dash()
	{
		if (Input::GetKeyUp(eKeyCode::SPACE))
		{
			mState = ePlayerState::Idle;
		}
	}

	void PlayerScript::jump()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKeyUp(eKeyCode::UP))
		{
			mState = ePlayerState::Idle;
		}
	}

	void PlayerScript::attack()
	{
		if (Input::GetKeyUp(eKeyCode::LBUTTON))
		{
			mState = ePlayerState::Idle;
		}

	}

	void PlayerScript::death()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void PlayerScript::OnCollisionStay(Collider2D* other)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* other)
	{
	}

}