#include "jsMaskedTortoiseScript.h"
#include "jsAnimator.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"
#include "jsGameObject.h"
#include "jsPlayer.h"
#include "jsPlayerScript.h"
#include "jsInput.h"
#include "jsRenderer.h"
#include "jsGameObject.h"
#include "jsTransform.h"
#include "jsTime.h"
#include "jsAttackRange.h"
#include "jsAttackRangeScript.h"
#include "jsObject.h"
#include "jsMaskedBullet.h"
#include "jsMaskedBulletScript.h"
#include "jsMaskedHead.h"
#include "jsMaskedHeadScript.h"
#include "jsRigidBody.h"
#include "jsAudioSource.h"

namespace js
{
	MaskedTortoiseScript::MaskedTortoiseScript()
		:mbRange(false)
		, mbRight(false)
		, mSpeed(1.0f)
		, dir(Vector3::Zero)
		, mTime(0.0f)
		, atCount(0)
		, hp(30.0f)
		, mbFly(false)
		, mbTouch(false)
		, mbHead(true)
		, deathTime(0.0f)
	{
	}
	MaskedTortoiseScript::~MaskedTortoiseScript()
	{
	}
	void MaskedTortoiseScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MonsterAnimationMaterial"));
		mAnimator = GetOwner()->AddComponent<Animator>();
		cd = GetOwner()->GetComponent<Collider2D>();
		cd->SetSize(Vector2(0.35f, 0.35f));
		cd->SetCenter(Vector2(0.1f, -0.2f));

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"MaskedTortoiseSprite", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\Masked Tortoise.png");
		mAnimator->Create(L"MaskedWait", atlas, Vector2(0.0f, 124.0f * 1), Vector2(129.0f, 124.0f), 5);
		mAnimator->Create(L"MaskedIdleRight", atlas, Vector2(0.0f, 124.0f * 2), Vector2(129.0f, 124.0f), 1);
		mAnimator->Create(L"MaskedMoveRight", atlas, Vector2(0.0f, 124.0f * 3), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedAttackRight", atlas, Vector2(0.0f, 124.0f * 5), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedEquipRight", atlas, Vector2(0.0f, 124.0f * 6), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"TurnMasked", atlas, Vector2(0.0f, 124.0f * 7), Vector2(129.0f, 124.0f), 5);
		mAnimator->Create(L"TurnNoMasked", atlas, Vector2(0.0f, 124.0f * 9), Vector2(129.0f, 124.0f), 5);
		mAnimator->Create(L"MaskedJumpRight", atlas, Vector2(0.0f, 124.0f * 10), Vector2(129.0f, 124.0f), 2);
		mAnimator->Create(L"NoMaskedIdleRight", atlas, Vector2(129.0f, 124.0f * 2), Vector2(129.0f, 124.0f), 1);

		mAnimator->Create(L"MaskedWaitLeft", atlas, Vector2(1215.0f, 124.0f * 1), Vector2(-129.0f, 124.0f), 5);
		mAnimator->Create(L"MaskedIdleLeft", atlas, Vector2(1215.0f, 124.0f * 2), Vector2(-129.0f, 124.0f), 1);
		mAnimator->Create(L"MaskedMoveLeft", atlas, Vector2(1215.0f, 124.0f * 3), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedAttackLeft", atlas, Vector2(1215.0f, 124.0f * 5), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedEquipLeft", atlas, Vector2(1215.0f, 124.0f * 6), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"TurnMasked", atlas, Vector2(1215.0f, 124.0f * 7), Vector2(-129.0f, 124.0f), 5);
		mAnimator->Create(L"TurnNoMasked", atlas, Vector2(1215.0f, 124.0f * 9), Vector2(-129.0f, 124.0f), 5);
		mAnimator->Create(L"MaskedJumpLeft", atlas, Vector2(1215.0f, 124.0f * 10), Vector2(-129.0f, 124.0f), 2);
		mAnimator->Create(L"NoMaskedIdleLeft", atlas, Vector2(1086.0f, 124.0f * 2), Vector2(-129.0f, 124.0f), 1);

		atlas = Resources::Load<Texture>(L"NoMaskedHit", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprHit_strip3.png");
		mAnimator->Create(L"NoMaskedHitRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 3, Vector2::Zero, 0.5f);
		mAnimator->Create(L"NoMaskedHitLeft", atlas, Vector2(258.0f, 0.0f), Vector2(-129.0f, 124.0f), 3, Vector2::Zero, 0.5f);

		atlas = Resources::Load<Texture>(L"NoMaskedMove", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprMoveNoMask_strip8.png");
		mAnimator->Create(L"NoMaskedMoveRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"NoMaskedMoveLeft", atlas, Vector2(903.0f, 0.0f), Vector2(-129.0f, 124.0f), 8);

		atlas = Resources::Load<Texture>(L"MaskedWing", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprSpawnWings_strip7.png");
		mAnimator->Create(L"MaskedWingRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 7);
		mAnimator->Create(L"MaskedWingLeft", atlas, Vector2(774.0f, 0.0f), Vector2(-129.0f, 124.0f), 7);

		atlas = Resources::Load<Texture>(L"MaskedFlyMove", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprFly_strip8.png");
		mAnimator->Create(L"MaskedFlyMoveRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedFlyMoveLeft", atlas, Vector2(903.0f, 0.0f), Vector2(-129.0f, 124.0f), 8);

		atlas = Resources::Load<Texture>(L"MaskedFlyShoot", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprFlyShoot_strip8.png");
		mAnimator->Create(L"MaskedFlyAttackRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedFlyAttackLeft", atlas, Vector2(903.0f, 0.0f), Vector2(-129.0f, 124.0f), 8);

		atlas = Resources::Load<Texture>(L"MaskedFlyEquip", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprFlyEquipMask_strip8.png");
		mAnimator->Create(L"MaskedFlyEquipRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedFlyEquipLeft", atlas, Vector2(903.0f, 0.0f), Vector2(-129.0f, 124.0f), 8);

		atlas = Resources::Load<Texture>(L"NoMaskedFlyMove", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprFlyNoMask_strip8.png");
		mAnimator->Create(L"NoMaskedFlyMoveRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"NoMaskedFlyMoveLeft", atlas, Vector2(903.0f, 0.0f), Vector2(-129.0f, 124.0f), 8);
		
		atlas = Resources::Load<Texture>(L"NoMaskedFlyDeath", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprFlyDeath.png");
		mAnimator->Create(L"MaskedFlyDeathRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 1);
		mAnimator->Create(L"MaskedFlyDeathLeft", atlas, Vector2(0.0f, 0.0f), Vector2(-129.0f, 124.0f), 1);
		
		atlas = Resources::Load<Texture>(L"Dust", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\dust.png");
		mAnimator->Create(L"dust", atlas, Vector2(0.0f, 0.0f), Vector2(40.0f, 26.0f), 6);

		reverseCB.monsterReverse = 1;
		reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
		reverseCb->SetData(&reverseCB);
		reverseCb->Bind(eShaderStage::PS);
		
		mAnimator->PlayAnimation(L"MaskedWaitLeft", true);
		mState = eMaskedState::Wait;

		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		dir = playerPos - monPos;
		dir.Normalize();

		msHead = object::Instantiate<MaskedHead>(Vector3(1000.0f, 1000.0f, 1000.0f), eLayerType::Artifact);
		msHead->SetName(L"msHead");
		msHead->AddComponent<Animator>();
		msHead->AddComponent<Collider2D>();
		msHead->AddComponent<MaskedHeadScript>();
		msHead->GetComponent<MaskedHeadScript>()->Initialize();

		// AttackRange
		atRange = object::Instantiate<AttackRange>(monPos, eLayerType::AttackRange);
		atRange->SetName(L"AttackRange");
		atRange->AddComponent<AttackRangeScript>();
		atRange->GetComponent<AttackRangeScript>()->Initialize();
		Transform* atRangeTr = atRange->GetComponent<Transform>();
		Collider2D* atRangeCd = atRange->AddComponent<Collider2D>();
		atRangeCd->SetSize(Vector2(4.5f, 3.5f));

	}
	void MaskedTortoiseScript::Update()
	{
		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		if (Input::GetKey(eKeyCode::P))
		{
			mAnimator->PlayAnimation(L"dust", true);
			mState = eMaskedState::Disappear;
		}

		if (hp == 15.0f)
		{
			mbFly = true;
			msHead->SetState(GameObject::eState::Dead);
			mState = eMaskedState::Idle;
		}
		if (hp < 0.0f)
		{
			hp = 1000.0f;
			if (monPos.x < playerPos.x)
				mbRight = true;
			else
				mbRight = false;

			mState = eMaskedState::Death;
			if (mbRight)
			{
				reverseCB.monsterReverse = 0;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
				mAnimator->PlayAnimation(L"MaskedFlyDeathRight", false);
			}
			else
			{
				reverseCB.monsterReverse = 1;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
				mAnimator->PlayAnimation(L"MaskedFlyDeathLeft", false);
			}
		}
		switch (mState)
		{
		case js::MaskedTortoiseScript::eMaskedState::Wait:
			wait();
			break;
		case js::MaskedTortoiseScript::eMaskedState::Idle:
			idle();
			break;
		case js::MaskedTortoiseScript::eMaskedState::Move:
			move();
			break;
		case js::MaskedTortoiseScript::eMaskedState::Attack:
			attack();
			break;
		case js::MaskedTortoiseScript::eMaskedState::Fly:
			fly();
			break;
		case js::MaskedTortoiseScript::eMaskedState::Hit:
			hit();
			break;
		case js::MaskedTortoiseScript::eMaskedState::ThrowHead:
			throwHead();
			break;
		case js::MaskedTortoiseScript::eMaskedState::PickUp:
			pickup();
			break;
		case js::MaskedTortoiseScript::eMaskedState::Death:
			death();
			break;
		case js::MaskedTortoiseScript::eMaskedState::Disappear:
			disappear();
			break;
		default:
			break;
		}
	}
	void MaskedTortoiseScript::wait()
	{
		mTime += Time::DeltaTime();
		if (mTime > 2.0f)
		{
			mAnimator->PlayAnimation(L"MaskedIdleRight", true);
			mState = eMaskedState::Idle;
			mTime = 0.0f;
		}
	}
	void MaskedTortoiseScript::idle()
	{
		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		if (monPos.x < playerPos.x)
			mbRight = true;
		else
			mbRight = false;

		mbRange = gPlayer->GetRange();

		if (!mbFly)
		{
			if (mbRight)
			{
				reverseCB.monsterReverse = 0;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
				mAnimator->PlayAnimation(L"MaskedMoveRight", true);
			}
			else
			{
				reverseCB.monsterReverse = 1;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
				mAnimator->PlayAnimation(L"MaskedMoveLeft", true);
			}
			mState = eMaskedState::Move;
		}
		else
		{
			if (mbRight)
			{
				reverseCB.monsterReverse = 0;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
				mAnimator->PlayAnimation(L"MaskedWingRight", false);
			}
			else
			{
				reverseCB.monsterReverse = 1;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
				mAnimator->PlayAnimation(L"MaskedWingLeft", false);
			}
			mState = eMaskedState::Fly;
		}
	}
	void MaskedTortoiseScript::move()
	{
		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();
		Transform* atRangeTr = atRange->GetComponent<Transform>();

		dir = playerPos - monPos;
		dir.Normalize();

		if (mbFly)
		{
			monPos += dir * mSpeed * Time::DeltaTime();
			if (monPos.x < playerPos.x)
			{
				reverseCB.monsterReverse = 0;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
			}
			else
			{
				reverseCB.monsterReverse = 1;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
			}

		}
		else
		{
			if (mbRight)
			{
				monPos.x += mSpeed * Time::DeltaTime();
			}
			else
			{
				monPos.x -= mSpeed * Time::DeltaTime();
			}
		}
		monTr->SetPosition(monPos);
		atRangeTr->SetPosition(monPos);

		mTime += Time::DeltaTime();

		if (mTime > 3.0f)
		{
			mTime = 0.0f;
			if (mbFly)
			{
				if (mbRight)
				{
					mAnimator->PlayAnimation(L"MaskedFlyAttackRight", true);
				}
				else
				{
					mAnimator->PlayAnimation(L"MaskedFlyAttackLeft", true);
				}
			}
			else
			{
				if (mbRight)
				{
					mAnimator->PlayAnimation(L"MaskedAttackRight", true);
				}
				else
				{
					mAnimator->PlayAnimation(L"MaskedAttackLeft", true);
				}
			}
			mState = eMaskedState::Attack;
		}
	}
	void MaskedTortoiseScript::attack()
	{
		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();
		Transform* atRangeTr = atRange->GetComponent<Transform>();

		dir = playerPos - monPos;
		dir.Normalize();

		if (mbFly)
		{
			monPos += dir * mSpeed * Time::DeltaTime();
			if (monPos.x < playerPos.x)
			{
				reverseCB.monsterReverse = 0;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
			}
			else
			{
				reverseCB.monsterReverse = 1;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
			}
		}
		else
		{
			if (mbRight)
			{
				monPos.x += mSpeed * Time::DeltaTime();
			}
			else
			{
				monPos.x -= mSpeed * Time::DeltaTime();
			}
		}

		monTr->SetPosition(monPos);
		atRangeTr->SetPosition(monPos);

		mTime += Time::DeltaTime();
		bool isRange = atRange->GetComponent<AttackRangeScript>()->IsRange();

		if (mTime > 0.2f)
		{
			AudioSource* as = GetOwner()->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"MaskedBulletSound", L"..\\Resources\\Sound\\SoundEffect\\bossFire.mp3"));
			as->Play();
			MaskedBullet* msBullet = object::Instantiate<MaskedBullet>(monPos, eLayerType::MonsterBullet);
			Transform* msbulletTr = msBullet->GetComponent<Transform>();
			msBullet->AddComponent<Collider2D>();
			msBullet->AddComponent<MaskedBulletScript>();
			msBullet->GetComponent<MaskedBulletScript>()->Initialize();
			atCount++;
			mTime = 0.0f;
		}

		if (atCount > 6)
		{
			mState = eMaskedState::Move;
			mTime = 0.0f;
			atCount = 0;
			if (mbFly)
			{
				if (mbRight)
				{
					mAnimator->PlayAnimation(L"MaskedFlyMoveRight", true);
				}
				else
				{
					mAnimator->PlayAnimation(L"MaskedFlyMoveLeft", true);
				}
			}
			else
			{
				if (mbRight)
				{
					mAnimator->PlayAnimation(L"MaskedMoveRight", true);
				}
				else
				{
					mAnimator->PlayAnimation(L"MaskedMoveLeft", true);
				}
			}
		}
	}
	void MaskedTortoiseScript::fly()
	{
		if (mAnimator->IsComplete())
		{
			if (mbRight)
			{
				reverseCB.monsterReverse = 0;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
				mAnimator->PlayAnimation(L"MaskedFlyMoveRight", true);
			}
			else
			{
				reverseCB.monsterReverse = 1;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
				mAnimator->PlayAnimation(L"MaskedFlyMoveLeft", true);
			}
			mState = eMaskedState::Move;
		}
	}
	void MaskedTortoiseScript::hit()
	{
		if (mAnimator->IsComplete())
		{
			if (mbFly)
			{
				if (mbRight)
					mAnimator->PlayAnimation(L"NoMaskedFlyMoveRight", true);
				else
					mAnimator->PlayAnimation(L"NoMaskedFlyMoveLeft", true);
			}
			else
			{
				if (mbRight)
					mAnimator->PlayAnimation(L"NoMaskedMoveRight", true);
				else
					mAnimator->PlayAnimation(L"NoMaskedMoveLeft", true);
			}
			mState = eMaskedState::ThrowHead;
		}
		
	}
	void MaskedTortoiseScript::death()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (mAnimator->IsComplete())
		{
			tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			mAnimator->PlayAnimation(L"dust", true);
			mState = eMaskedState::Disappear;
		}
	}
	void MaskedTortoiseScript::pickup()
	{
		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		if (monPos.x < playerPos.x)
			mbRight = true;
		else
			mbRight = false;

		if (mAnimator->IsComplete())
		{
			if (mbFly)
			{
				if (mbRight)
				{
					reverseCB.monsterReverse = 0;
					reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
					reverseCb->SetData(&reverseCB);
					reverseCb->Bind(eShaderStage::PS);
					mAnimator->PlayAnimation(L"MaskedFlyMoveRight", true);
				}
				else
				{
					reverseCB.monsterReverse = 1;
					reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
					reverseCb->SetData(&reverseCB);
					reverseCb->Bind(eShaderStage::PS);
					mAnimator->PlayAnimation(L"MaskedFlyMoveLeft", true);
				}
			}
			else
			{
				if (mbRight)
				{
					reverseCB.monsterReverse = 0;
					reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
					reverseCb->SetData(&reverseCB);
					reverseCb->Bind(eShaderStage::PS);
					mAnimator->PlayAnimation(L"MaskedMoveRight", true);
				}
				else
				{
					reverseCB.monsterReverse = 1;
					reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
					reverseCb->SetData(&reverseCB);
					reverseCb->Bind(eShaderStage::PS);
					mAnimator->PlayAnimation(L"MaskedMoveLeft", true);
				}
			}
			mState = eMaskedState::Move;
			mbTouch = false;
			mbHead = true;
		}
		
	}
	void MaskedTortoiseScript::throwHead()
	{
		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* headTr = msHead->GetComponent<Transform>();
		Vector3 headPos = headTr->GetPosition();

		Vector3 headDir = headPos - monPos;
		headDir.Normalize();
		if (mbFly)
		{
			monPos += headDir * mSpeed * Time::DeltaTime();
		}
		else
		{
			if (monPos.x < headPos.x)
				monPos.x += mSpeed * Time::DeltaTime();
			else
				monPos.x -= mSpeed * Time::DeltaTime();
		}

		monTr->SetPosition(monPos);
	}
	void MaskedTortoiseScript::disappear()
	{
		deathTime += Time::DeltaTime();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		const float pi = 3.141592f;
		float degree = pi / 2.0f;
		tr->SetRotation(Vector3(0.0f, 0.0f, degree * deathTime));
		if (deathTime > 3.0f)
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}
	}
	void MaskedTortoiseScript::OnCollisionEnter(Collider2D* other)
	{
		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		collisionCB.collision = 1;
		collisionCb = renderer::constantBuffer[(UINT)eCBType::Collision];
		collisionCb->SetData(&collisionCB);
		collisionCb->Bind(eShaderStage::PS);

		if (other->GetOwner()->GetName().compare(L"BossLeftWall") == 0)
		{
			if(!mbFly)
				mAnimator->PlayAnimation(L"MaskedIdleRight", true);
			mState = eMaskedState::Idle;
		}
		if (other->GetOwner()->GetName().compare(L"BossRightWall") == 0)
		{
			if(!mbFly)
				mAnimator->PlayAnimation(L"MaskedIdleLeft", true);
			mState = eMaskedState::Idle;
		}
		if (other->GetOwner()->GetName().compare(L"PlayerAttack") == 0)
		{
			msHead = object::Instantiate<MaskedHead>(Vector3(monPos), eLayerType::Artifact);
			msHead->SetName(L"msHead");
			msHead->AddComponent<Animator>();
			msHead->AddComponent<Collider2D>();
			msHead->AddComponent<MaskedHeadScript>();
			msHead->GetComponent<MaskedHeadScript>()->Initialize();
			if (monPos.x < playerPos.x)
			{
				// 왼쪽으로 날아가야함
				mbRight = false;
				reverseCB.monsterReverse = 1;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
				mAnimator->PlayAnimation(L"NoMaskedHitLeft", false);
				msHead->GetComponent<MaskedHeadScript>()->SetRightDir(false);
			}
			else
			{
				// 오른쪽으로 날아가야함
				mbRight = true;
				reverseCB.monsterReverse = 0;
				reverseCb = renderer::constantBuffer[(UINT)eCBType::MonsterReverse];
				reverseCb->SetData(&reverseCB);
				reverseCb->Bind(eShaderStage::PS);
				mAnimator->PlayAnimation(L"NoMaskedHitRight", false);
				msHead->GetComponent<MaskedHeadScript>()->SetRightDir(true);
			}
			mbHead = false;
			mbTouch = true;
			mState = eMaskedState::Hit;
		}
		if (msHead->GetComponent<Rigidbody>()->GetGround())
		{
			if (other->GetOwner()->GetName().compare(L"msHead") == 0)
			{
				if (mbFly)
				{
					if (mbRight)
						mAnimator->PlayAnimation(L"MaskedFlyEquipRight", false);
					else
						mAnimator->PlayAnimation(L"MaskedFlyEquipLeft", false);
				}
				else
				{
					if (mbRight)
						mAnimator->PlayAnimation(L"MaskedEquipRight", false);
					else
						mAnimator->PlayAnimation(L"MaskedEquipLeft", false);
				}
				mState = eMaskedState::PickUp;
				msHead->SetState(GameObject::eState::Dead);
			}
		}
		if (other->GetOwner()->GetName().compare(L"GeddyBullet") == 0)
		{
			if(mbTouch)
				hp -= 1.0f;
		}

	}
	void MaskedTortoiseScript::OnCollisionStay(Collider2D* other)
	{

	}
	void MaskedTortoiseScript::OnCollisionExit(Collider2D* other)
	{
		collisionCB.collision = 0;

		collisionCb = renderer::constantBuffer[(UINT)eCBType::Collision];
		collisionCb->SetData(&collisionCB);
		collisionCb->Bind(eShaderStage::PS);
	}
}