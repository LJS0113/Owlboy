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


namespace js
{
	PlayerScript::PlayerScript()
		: mState(ePlayerState::None)
		, mbFly(false)
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
		mAnimator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"OtusSpriteRight", L"..\\Resources\\Texture\\Otus\\OtusIdle.png");
		mAnimator->Create(L"OtusIdleRight", atlas, Vector2(0.0f, 0.0f), Vector2(70.0f, 125.0f), 10);
		mAnimator->Create(L"OtusIdleLeft", atlas, Vector2(0.0f, 125.0f), Vector2(70.0f, 125.0f), 10);

		atlas = Resources::Load<Texture>(L"OtusWalk", L"..\\Resources\\Texture\\Otus\\OtusWalk.png");
		mAnimator->Create(L"OtusMoveRight", atlas, Vector2(0.0f, 0.0f), Vector2(125.0f, 135.0f), 8);
		mAnimator->Create(L"OtusMoveLeft", atlas, Vector2(0.0f, 135.0f), Vector2(125.0f, 135.0f), 8);

		atlas = Resources::Load<Texture>(L"OtusJump", L"..\\Resources\\Texture\\Otus\\OtusJump.png");
		mAnimator->Create(L"OtusJumpRight", atlas, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), 3);
		mAnimator->Create(L"OtusJumpLeft", atlas, Vector2(0.0f, 130.0f), Vector2(120.0f, 130.0f), 3);
		mAnimator->PlayAnimation(L"OtusIdleRight", true);

		atlas = Resources::Load<Texture>(L"OtusJumpFall", L"..\\Resources\\Texture\\Otus\\otusJumpFall_700x280_5x2.bmp");
		mAnimator->Create(L"OtusJumpFallRight", atlas, Vector2(0.0f, 0.0f), Vector2(140.0f, 140.0f), 5);
		mAnimator->Create(L"OtusJumpFallLeft", atlas, Vector2(0.0f, 140.0f), Vector2(140.0f, 140.0f), 5);

		atlas = Resources::Load<Texture>(L"OtusDash", L"..\\Resources\\Texture\\Otus\\otusRoll_1200x400_4x2.bmp");
		mAnimator->Create(L"OtusDashRight", atlas, Vector2(0.0f, 0.0f), Vector2(300.0f, 200.0f), 4);
		mAnimator->Create(L"OtusDashLeft", atlas, Vector2(0.0f, 200.0f), Vector2(300.0f, 200.0f), 4);

		atlas = Resources::Load<Texture>(L"OtusAttackusDash", L"..\\Resources\\Texture\\Otus\\otusAttack_1350x260_5x2.bmp");
		mAnimator->Create(L"OtusAttackRight", atlas, Vector2(0.0f, 0.0f), Vector2(270.0f, 130.0f), 5);
		mAnimator->Create(L"OtusAttackLeft", atlas, Vector2(0.0f, 130.0f), Vector2(270.0f, 130.0f), 5);

		atlas = Resources::Load<Texture>(L"OtusFly", L"..\\Resources\\Texture\\Otus\\otusFly_1530x390_6x2.bmp");
		mAnimator->Create(L"OtusFlyRight", atlas, Vector2(0.0f, 0.0f), Vector2(255.0f, 195.0f), 6);
		mAnimator->Create(L"OtusFlyLeft", atlas, Vector2(0.0f, 195.0f), Vector2(255.0f, 195.0f), 6);


		mAnimator->PlayAnimation(L"OtusIdleRight", true);
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
			if(!mbFly)
				mAnimator->PlayAnimation(L"OtusIdleRight", true);
			if(mbFly)
				mAnimator->PlayAnimation(L"OtusFlyRight", true);
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
			mAnimator->PlayAnimation(L"OtusJumpFallRight", true);
			mState = ePlayerState::Move;
			mbFly = false;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			if (mbFly)
				mAnimator->PlayAnimation(L"OtusFlyLeft", true);
			else
				mAnimator->PlayAnimation(L"OtusMoveLeft", true);
			mState = ePlayerState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			if (mbFly)
				mAnimator->PlayAnimation(L"OtusFlyRight", true);
			else
				mAnimator->PlayAnimation(L"OtusMoveRight", true);
			mState = ePlayerState::Move;
		}


		if (Input::GetKeyDown(eKeyCode::UP))
		{
			mAnimator->PlayAnimation(L"OtusFlyRight", true);
			mbFly = true;
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mAnimator->PlayAnimation(L"OtusAttackRight", false);
			mState = ePlayerState::Attack;
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			mAnimator->PlayAnimation(L"OtusDashRight", false);
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
			if(!mbFly)
				mState = ePlayerState::Idle;

		}
	}

	void PlayerScript::attack()
	{
		if (Input::GetKeyUp(eKeyCode::LBUTTON))
		{
			mAnimator->PlayAnimation(L"OtusIdleRight", true);
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