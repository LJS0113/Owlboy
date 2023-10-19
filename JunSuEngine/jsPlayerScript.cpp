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
#include "jsObject.h"
#include "jsGeddy.h"
#include "jsGeddyScript.h"
#include "jsAttackObject.h"
#include "jsAudioSource.h"
#include "jsGeddyArm.h"
#include "jsGeddyArmScript.h"
#include "jsGeddyBullet.h"
#include "jsGeddyBulletScript.h"

extern js::Geddy* gGeddy;

namespace js
{
	PlayerScript::PlayerScript()
		: mState(ePlayerState::None)
		, mbFly(false)
		, mAnimator(nullptr)
		, mbRight(true)
		, mbHang(false)
		, mbSummon(false)
		, mSpeed(3.0f)
		, reverseCb(nullptr)
		, reverseCB{}
		, collisionCB{}
		, collisionCb(nullptr)
		, atObj(nullptr)
		, as(nullptr)
	{
		reverseCB.reverse = 0;

		reverseCb = renderer::constantBuffer[(UINT)eCBType::Reverse];
		reverseCb->SetData(&reverseCB);
		reverseCb->Bind(eShaderStage::PS);

		collisionCB.collision = 0;

		collisionCb = renderer::constantBuffer[(UINT)eCBType::Collision];
		collisionCb->SetData(&collisionCB);
		collisionCb->Bind(eShaderStage::PS);
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteReverseAnimationMaterial"));
		mAnimator = GetOwner()->AddComponent<Animator>();
		cd = GetOwner()->GetComponent<Collider2D>();

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

		atlas = Resources::Load<Texture>(L"OtusDashSprite", L"..\\Resources\\Texture\\Otus\\rollGround_strip6.png");
		mAnimator->Create(L"OtusDashRight", atlas, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), 6, Vector2::Zero, 0.06f);
		mAnimator->Create(L"OtusDashLeft", atlas, Vector2(560.0f, 0.0f), Vector2(-112.0f, 96.0f), 6, Vector2::Zero, 0.06f);

		atlas = Resources::Load<Texture>(L"OtusFlyDashSprite", L"..\\Resources\\Texture\\Otus\\roll_strip9.png");
		mAnimator->Create(L"OtusFlyDashRight", atlas, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), 9, Vector2::Zero, 0.06f);
		mAnimator->Create(L"OtusFlyDashLeft", atlas, Vector2(896.0f, 0.0f), Vector2(-112.0f, 96.0f), 9, Vector2::Zero, 0.06f);

		mAnimator->PlayAnimation(L"OtusIdleRight", true);
		mState = ePlayerState::Idle;

		atObj = object::Instantiate<AttackObject>(Vector3(1000.0f, 1000.0f, 1000.0f), eLayerType::PlayerAttack);
		atObj->SetName(L"PlayerAttack");


	}

	void PlayerScript::Update()
	{
		if (mbRight)
		{
			// 오른쪽이면 0, 왼쪽이면 1
			reverseCB.reverse = 0;

			reverseCb = renderer::constantBuffer[(UINT)eCBType::Reverse];
			reverseCb->SetData(&reverseCB);
			reverseCb->Bind(eShaderStage::PS);
		}
		else
		{
			// 오른쪽이면 0, 왼쪽이면 1
			reverseCB.reverse = 1;

			reverseCb = renderer::constantBuffer[(UINT)eCBType::Reverse];
			reverseCb->SetData(&reverseCB);
			reverseCb->Bind(eShaderStage::PS);
		}

		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector2 pos = Input::GetMousePos();
		//Vector3 mousePos = Vector3(pos.x, pos.y, 1.0f);
		//mousePos = tr->GetNDCPos(Vector3(mousePos.x, mousePos.y, mousePos.z));

		//float rad = atan2(mousePos.x, mousePos.y);
		//tr->SetRotation(Vector3(0.0f, 0.0f, -rad));

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
		case js::PlayerScript::ePlayerState::Hang:
			hang();
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
		case js::PlayerScript::ePlayerState::Fall:
			fall();
			break;
		default:
			break;
		}

	}

	void PlayerScript::Complete()
	{
	}


	void PlayerScript::move()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::A))
		{
			cd->SetCenter(Vector2(0.1f, -0.05f));
			if (Input::GetKey(eKeyCode::S))
			{
				pos.y -= mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::W))
			{
				if (mbFly)
				{
					pos.y += mSpeed * Time::DeltaTime();
				}
				else
				{
					if (mbRight)
						mAnimator->PlayAnimation(L"OtusJumpRight", false);
					else
						mAnimator->PlayAnimation(L"OtusJumpLeft", false);
					mState = ePlayerState::Jump;
				}
			}
			pos.x -= mSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mState = ePlayerState::Move;
		}

		else if (Input::GetKey(eKeyCode::D))
		{
			if (Input::GetKey(eKeyCode::S))
			{
				pos.y -= mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::W))
			{
				if (mbFly)
				{
					pos.y += mSpeed * Time::DeltaTime();
				}
				else
				{
					if (mbRight)
						mAnimator->PlayAnimation(L"OtusJumpRight", false);
					else
						mAnimator->PlayAnimation(L"OtusJumpLeft", false);
					mState = ePlayerState::Jump;
				}
			}
			cd->SetSize(Vector2(0.1f, 0.2f));
			cd->SetCenter(Vector2(-0.1f, -0.05f));
			pos.x += mSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mState = ePlayerState::Move;
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			pos.y -= mSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mState = ePlayerState::Move;
		}
		else if (Input::GetKey(eKeyCode::W))
		{
			pos.y += mSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyUp(eKeyCode::S)
			|| Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::D)
			|| Input::GetKeyUp(eKeyCode::W))
		{
			if (mbHang)
			{
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusHangRight", true);
				else
					mAnimator->PlayAnimation(L"OtusHangLeft", true);
				mState = ePlayerState::Hang;
			}
			else
			{
				if (!mbFly)
				{
					if (mbRight)
						mAnimator->PlayAnimation(L"OtusIdleRight", true);
					else
						mAnimator->PlayAnimation(L"OtusIdleLeft", true);
					mState = ePlayerState::Idle;
				}
				else
				{
					if (mbRight)
						mAnimator->PlayAnimation(L"OtusFlyRight", true);
					else
						mAnimator->PlayAnimation(L"OtusFlyLeft", true);
					mState = ePlayerState::Fly;
				}
			}
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (!mbHang)
			{
				as = GetOwner()->AddComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"PlayerAttack", L"..\\Resources\\Sound\\SoundEffect\\attack.mp3"));
				as->Play();
				atObj = object::Instantiate<AttackObject>(pos, eLayerType::PlayerAttack);
				atObj->SetName(L"PlayerAttack");
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusAttackRight", false);
				else
					mAnimator->PlayAnimation(L"OtusAttackLeft", false);

			}
			else
			{
				Transform* geddyTr = gGeddy->GetComponent<Transform>();
				Vector3 geddyPos = geddyTr->GetPosition();

				GeddyBullet* bullet = object::Instantiate<GeddyBullet>(Vector3(geddyPos), eLayerType::PlayerBullet);
				bullet->SetName(L"GeddyBullet");
				MeshRenderer* mr = bullet->AddComponent<MeshRenderer>();
				as = GetOwner()->AddComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"GeddyBulletSound", L"..\\Resources\\Sound\\SoundEffect\\geddyFire.mp3"));
				as->Play();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
				bullet->AddComponent<Collider2D>();
				bullet->AddComponent<Transform>();
				bullet->AddComponent<GeddyBulletScript>();
				bullet->GetComponent<GeddyBulletScript>()->Initialize();
			}
			mState = ePlayerState::Attack;
		}

		if (Input::GetKeyDown(eKeyCode::R))
		{
			if (!mbSummon)
			{
				// 첫 소환
				gGeddy = object::Instantiate<Geddy>(Vector3(pos.x, pos.y - 0.5f, pos.z), eLayerType::Player);
				gGeddy->SetName(L"Geddy");
				MeshRenderer* mr = gGeddy->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
				gGeddy->AddComponent<Transform>();
				Transform* geddyTr = gGeddy->GetComponent<Transform>();
				Vector3 geddyPos = geddyTr->GetPosition();
				Collider2D* geddyCd = gGeddy->AddComponent<Collider2D>();
				Rigidbody* geddyRb = gGeddy->AddComponent<Rigidbody>();
				gGeddy->AddComponent<GeddyScript>();
				gGeddy->GetComponent<GeddyScript>()->Initialize();
				geddyTr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
				geddyCd->SetColliderOwner(eColliderOwner::Player);

				GeddyArm* geddyArm = object::Instantiate<GeddyArm>(Vector3(2.0f, 2.0f, 1.0f), eLayerType::Player);
				geddyArm->SetName(L"GeddyArm");
				mr = geddyArm->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
				geddyArm->AddComponent<Transform>();
				Transform* geddyArmTr = geddyArm->GetComponent<Transform>();
				Vector3 geddyArmPos = geddyArmTr->GetPosition();
				geddyArm->AddComponent<GeddyArmScript>();
				geddyArm->GetComponent<GeddyArmScript>()->Initialize();
				mbSummon = true;
				mbHang = true;
			}
			mbHang = true;

			if (mbRight)
				mAnimator->PlayAnimation(L"OtusHangRight", true);
			else
				mAnimator->PlayAnimation(L"OtusHangLeft", true);
			mState = ePlayerState::Hang;
		}

		if (Input::GetKeyDown(eKeyCode::RBUTTON))
		{
			if (!mbHang)
			{
				rb->SetGround(false);
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusFallRight", true);
				else
					mAnimator->PlayAnimation(L"OtusFallLeft", true);
				mState = ePlayerState::Fall;
			}
			else
			{
				mbHang = false;
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusFlyRight", true);
				else
					mAnimator->PlayAnimation(L"OtusFlyLeft", true);
				mState = ePlayerState::Fly;
			}
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			if (mbFly)
			{
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusFlyDashRight", false);
				else
					mAnimator->PlayAnimation(L"OtusFlyDashLeft", false);
			}
			else
			{
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusDashRight", false);
				else
					mAnimator->PlayAnimation(L"OtusDashLeft", false);
			}
			mState = ePlayerState::Dash;
		}

	}

	void PlayerScript::idle()
	{

		//Animator* at = GetOwner()->GetComponent<Animator>();
		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		cd->SetSize(Vector2(0.1f, 0.2f));
		if (mbRight)
			cd->SetCenter(Vector2(-0.1f, -0.05f));
		else
			cd->SetCenter(Vector2(0.1f, -0.05f));

		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mbRight)
				mAnimator->PlayAnimation(L"OtusFlyRight", false);
			else
				mAnimator->PlayAnimation(L"OtusFlyLeft", false);
			mState = ePlayerState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mbRight = false;
			if (mbFly)
				mAnimator->PlayAnimation(L"OtusFlyLeft", true);
			else
				mAnimator->PlayAnimation(L"OtusMoveLeft", true);
			mState = ePlayerState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			mbRight = true;
			if (mbFly)
				mAnimator->PlayAnimation(L"OtusFlyRight", true);
			else
				mAnimator->PlayAnimation(L"OtusMoveRight", true);
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			if (!mbFly)
			{
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusJumpRight", false);
				else
					mAnimator->PlayAnimation(L"OtusJumpLeft", false);
				mState = ePlayerState::Jump;
			}
			else
			{
				mState = ePlayerState::Move;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (!mbHang)
			{
				as = GetOwner()->AddComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"PlayerAttack", L"..\\Resources\\Sound\\SoundEffect\\attack.mp3"));
				as->Play();
				atObj = object::Instantiate<AttackObject>(pos, eLayerType::PlayerAttack);
				atObj->SetName(L"PlayerAttack");
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusAttackRight", false);
				else
					mAnimator->PlayAnimation(L"OtusAttackLeft", false);
				mState = ePlayerState::Attack;
			}
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			if (mbRight)
				mAnimator->PlayAnimation(L"OtusDashRight", false);
			else
				mAnimator->PlayAnimation(L"OtusDashLeft", false);
			mState = ePlayerState::Dash;
		}

		if (Input::GetKeyDown(eKeyCode::RBUTTON))
		{
			if (!mbHang)
			{
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusFallRight", false);
				else
					mAnimator->PlayAnimation(L"OtusFallLeft", false);
				mState = ePlayerState::Fall;
			}
			mbHang = false;
		}
	}

	void PlayerScript::dash()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		if(mbRight)
			pos.x += mSpeed * 1.5f * Time::DeltaTime();
		else
			pos.x -= mSpeed * 1.5f * Time::DeltaTime();

		tr->SetPosition(pos);
		if (mAnimator->IsComplete())
		{
			if (mbHang)
			{
				// 메달려있을때
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusHangRight", true);
				else
					mAnimator->PlayAnimation(L"OtusHangLeft", true);
				mState = ePlayerState::Hang;
			}
			else
			{
				// 안 메달려 있을때 
				if (mbFly)
				{
					// 날고 있을때
					if (mbRight)
						mAnimator->PlayAnimation(L"OtusFlyRight", true);
					else
						mAnimator->PlayAnimation(L"OtusFlyLeft", true);
					mState = ePlayerState::Fly;
				}
				else
				{
					// 안날고 있을때
					if (mbRight)
						mAnimator->PlayAnimation(L"OtusIdleRight", true);
					else
						mAnimator->PlayAnimation(L"OtusIdleLeft", true);
					mState = ePlayerState::Idle;
				}
			}
		}
	}

	void PlayerScript::jump()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		rb->SetGround(false);
		pos.y += mSpeed * Time::DeltaTime();
		tr->SetPosition(pos);

		if (mAnimator->IsComplete())
		{
			if (!mbFly)
			{
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusFallRight", false);
				else
					mAnimator->PlayAnimation(L"OtusFallLeft", false);
				mState = ePlayerState::Fall;
				mbFly = false;
			}
		}
		else if (Input::GetKeyDown(eKeyCode::W))
		{
			as = GetOwner()->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"PlayerWing", L"..\\Resources\\Sound\\SoundEffect\\wing.mp3"));
			as->Play();

			if (mbRight)
				mAnimator->PlayAnimation(L"OtusFlyRight", true);
			else
				mAnimator->PlayAnimation(L"OtusFlyLeft", true);
			rb->SetGround(true);
			mbFly = true;
			mState = ePlayerState::Fly;
		}
	}

	void PlayerScript::hang()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		rb->SetGround(true);
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::A))
		{
			mbRight = false;
			mAnimator->PlayAnimation(L"OtusHangLeft", true);
			mState = ePlayerState::Move;
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			mbRight = true;
			mAnimator->PlayAnimation(L"OtusHangRight", true);
			mState = ePlayerState::Move;
		}
		else if (Input::GetKey(eKeyCode::S) || Input::GetKey(eKeyCode::W))
		{
			if (mbRight)
				mAnimator->PlayAnimation(L"OtusHangRight", true);
			else
				mAnimator->PlayAnimation(L"OtusHangLeft", true);
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			Transform* geddyTr = gGeddy->GetComponent<Transform>();
			Vector3 geddyPos = geddyTr->GetPosition();

			GeddyBullet* bullet = object::Instantiate<GeddyBullet>(Vector3(geddyPos), eLayerType::PlayerBullet);
			bullet->SetName(L"GeddyBullet");
			MeshRenderer* mr = bullet->AddComponent<MeshRenderer>();
			as = GetOwner()->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"GeddyBulletSound", L"..\\Resources\\Sound\\SoundEffect\\geddyFire.mp3"));
			as->Play();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			bullet->AddComponent<Collider2D>();
			bullet->AddComponent<Transform>();
			bullet->AddComponent<GeddyBulletScript>();
			bullet->GetComponent<GeddyBulletScript>()->Initialize();
		}
		if (Input::GetKeyDown(eKeyCode::RBUTTON))
		{
			if (!mbHang)
			{
				rb->SetGround(false);
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusFallRight", true);
				else
					mAnimator->PlayAnimation(L"OtusFallLeft", true);
				mState = ePlayerState::Fall;
			}
			else
			{
				mbHang = false;
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusFlyRight", true);
				else
					mAnimator->PlayAnimation(L"OtusFlyLeft", true);
				mState = ePlayerState::Fly;
			}
		}
	}

	void PlayerScript::attack()
	{
		if (!mbHang)
		{
			if (mAnimator->IsComplete())
			{
				if (!mbFly)
				{
					if (mbRight)
						mAnimator->PlayAnimation(L"OtusIdleRight", true);
					else
						mAnimator->PlayAnimation(L"OtusIdleLeft", true);
					mState = ePlayerState::Idle;
				}
				if (mbFly)
				{
					if (mbRight)
						mAnimator->PlayAnimation(L"OtusFlyRight", true);
					else
						mAnimator->PlayAnimation(L"OtusFlyLeft", true);
					mState = ePlayerState::Fly;
				}
				atObj->SetState(GameObject::eState::Dead);
				as->Stop();
			}
		}
		else
		{
			mState = ePlayerState::Hang;
		}

	}

	void PlayerScript::death()
	{
	}

	void PlayerScript::fly()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::A))
		{
			mbRight = false;
			mAnimator->PlayAnimation(L"OtusFlyLeft", true);
			mState = ePlayerState::Move;
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			mbRight = true;
			mAnimator->PlayAnimation(L"OtusFlyRight", true);
			mState = ePlayerState::Move;
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			if (mbRight)
				mAnimator->PlayAnimation(L"OtusFlyRight", true);
			else
				mAnimator->PlayAnimation(L"OtusFlyLeft", true);
			mState = ePlayerState::Move;
		}
		else if (Input::GetKey(eKeyCode::W))
		{
			if (mbRight)
				mAnimator->PlayAnimation(L"OtusFlyRight", true);
			else
				mAnimator->PlayAnimation(L"OtusFlyLeft", true);
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::R))
		{
			if (!mbSummon)
			{
				// 첫 소환
				gGeddy = object::Instantiate<Geddy>(Vector3(pos.x, pos.y - 0.5f, pos.z), eLayerType::Player);
				gGeddy->SetName(L"Geddy");
				MeshRenderer* mr = gGeddy->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
				gGeddy->AddComponent<Transform>();
				Transform* geddyTr = gGeddy->GetComponent<Transform>();
				Vector3 geddyPos = geddyTr->GetPosition();
				Collider2D* geddyCd = gGeddy->AddComponent<Collider2D>();
				Rigidbody* geddyRb = gGeddy->AddComponent<Rigidbody>();
				gGeddy->AddComponent<GeddyScript>();
				gGeddy->GetComponent<GeddyScript>()->Initialize();
				geddyTr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
				geddyCd->SetColliderOwner(eColliderOwner::Player);

				GeddyArm* geddyArm = object::Instantiate<GeddyArm>(Vector3(2.0f, 2.0f, 1.0f), eLayerType::Player);
				geddyArm->SetName(L"GeddyArm");
				mr = geddyArm->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
				geddyArm->AddComponent<Transform>();
				Transform* geddyArmTr = geddyArm->GetComponent<Transform>();
				Vector3 geddyArmPos = geddyArmTr->GetPosition();
				geddyArm->AddComponent<GeddyArmScript>();
				geddyArm->GetComponent<GeddyArmScript>()->Initialize();
				mbHang = true;
				mbSummon = true;
			}
			mbHang = true;

			if (mbRight)
				mAnimator->PlayAnimation(L"OtusHangRight", true);
			else
				mAnimator->PlayAnimation(L"OtusHangLeft", true);
			mState = ePlayerState::Hang;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (!mbHang)
			{
				as = GetOwner()->AddComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"PlayerAttack", L"..\\Resources\\Sound\\SoundEffect\\attack.mp3"));
				as->Play();
				atObj = object::Instantiate<AttackObject>(pos, eLayerType::PlayerAttack);
				atObj->SetName(L"PlayerAttack");
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusAttackRight", false);
				else
					mAnimator->PlayAnimation(L"OtusAttackLeft", false);
			}
			mState = ePlayerState::Attack;
		}

		if (Input::GetKeyDown(eKeyCode::RBUTTON))
		{
			rb->SetGround(false);
			if (!mbHang)
			{
				if (mbRight)
					mAnimator->PlayAnimation(L"OtusJumpFallRight", true);
				else
					mAnimator->PlayAnimation(L"OtusJumpFallLeft", true);
				mState = ePlayerState::Fall;
				mbHang = false;
			}
		}
	}

	void PlayerScript::fall()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		if (rb->GetGround())
		{
			mbFly = false;
			if (mbRight)
				mAnimator->PlayAnimation(L"OtusIdleRight", true);
			else
				mAnimator->PlayAnimation(L"OtusIdleLeft", true);
			mState = ePlayerState::Idle;
		}
	}

	void PlayerScript::OnCollisionEnter(Collider2D* other)
	{
		collisionCB.collision = 1;

		collisionCb = renderer::constantBuffer[(UINT)eCBType::Collision];
		collisionCb->SetData(&collisionCB);
		collisionCb->Bind(eShaderStage::PS);
	}
	void PlayerScript::OnCollisionStay(Collider2D* other)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* other)
	{
		collisionCB.collision = 0;

		collisionCb = renderer::constantBuffer[(UINT)eCBType::Collision];
		collisionCb->SetData(&collisionCB);
		collisionCb->Bind(eShaderStage::PS);
	}

}