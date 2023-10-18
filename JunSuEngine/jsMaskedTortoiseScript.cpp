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

namespace js
{
	MaskedTortoiseScript::MaskedTortoiseScript()
		:mbRange(false)
		, mbRight(false)
		, mSpeed(0.8f)
		, dir(Vector3::Zero)
		, mTime(0.0f)
		, atCount(0)
		
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
		mAnimator->Create(L"MaskedIdleRight", atlas, Vector2(0.0f, 124.0f * 2), Vector2(129.0f, 124.0f), 1);
		mAnimator->Create(L"MaskedMoveRight", atlas, Vector2(0.0f, 124.0f * 3), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedAttackRight", atlas, Vector2(0.0f, 124.0f * 5), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedEquipRight", atlas, Vector2(0.0f, 124.0f * 6), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"TurnMasked", atlas, Vector2(0.0f, 124.0f * 7), Vector2(129.0f, 124.0f), 5);
		mAnimator->Create(L"TurnNoMasked", atlas, Vector2(0.0f, 124.0f * 9), Vector2(129.0f, 124.0f), 5);
		mAnimator->Create(L"MaskedJumpRight", atlas, Vector2(0.0f, 124.0f * 10), Vector2(129.0f, 124.0f), 2);
		mAnimator->Create(L"MaskedWingRight", atlas, Vector2(0.0f, 124.0f * 11), Vector2(129.0f, 124.0f), 7);
		mAnimator->Create(L"MaskedFlyMoveRight", atlas, Vector2(0.0f, 124.0f * 12), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedFlyEquipRight", atlas, Vector2(0.0f, 124.0f * 13), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedFlyAttackRight", atlas, Vector2(0.0f, 124.0f * 15), Vector2(129.0f, 124.0f), 8);
		//mAnimator->Create(L"FlyingMaskRight", atlas, Vector2(0.0f, 124.0f * 17), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"FlyingMaskRight", atlas, Vector2(0.0f, 124.0f * 18), Vector2(129.0f, 124.0f), 9);
		mAnimator->Create(L"MaskedFlyDeathRight", atlas, Vector2(0.0f, 124.0f * 19), Vector2(129.0f, 124.0f), 1);

		mAnimator->Create(L"NoMaskedIdleRight", atlas, Vector2(129.0f, 124.0f * 2), Vector2(129.0f, 124.0f), 1);
		mAnimator->Create(L"NoMaskedMoveRight", atlas, Vector2(0.0f, 124.0f * 8), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"NoMaskedFlyRight", atlas, Vector2(0.0f, 124.0f * 14), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"NoMaskedHitRight", atlas, Vector2(0.0f, 124.0f * 16), Vector2(129.0f, 124.0f), 6);


		mAnimator->Create(L"MaskedIdleLeft", atlas, Vector2(1215.0f, 124.0f * 2), Vector2(-129.0f, 124.0f), 1);
		mAnimator->Create(L"MaskedMoveLeft", atlas, Vector2(1215.0f, 124.0f * 3), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedAttackLeft", atlas, Vector2(1215.0f, 124.0f * 5), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedEquipLeft", atlas, Vector2(1215.0f, 124.0f * 6), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"TurnMasked", atlas, Vector2(1215.0f, 124.0f * 7), Vector2(-129.0f, 124.0f), 5);
		mAnimator->Create(L"TurnNoMasked", atlas, Vector2(1215.0f, 124.0f * 9), Vector2(-129.0f, 124.0f), 5);
		mAnimator->Create(L"MaskedJumpLeft", atlas, Vector2(1215.0f, 124.0f * 10), Vector2(-129.0f, 124.0f), 2);
		mAnimator->Create(L"MaskedWingLeft", atlas, Vector2(1215.0f, 124.0f * 11), Vector2(-129.0f, 124.0f), 7);
		mAnimator->Create(L"MaskedFlyMoveLeft", atlas, Vector2(1215.0f, 124.0f * 12), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedFlyEquipLeft", atlas, Vector2(1215.0f, 124.0f * 13), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"MaskedFlyAttackLeft", atlas, Vector2(1215.0f, 124.0f * 15), Vector2(-129.0f, 124.0f), 8);
		//mAnimator->Create(L"FlyingMaskLeft", atlas, Vector2(1215.0f, 124.0f * 17), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"FlyingMaskLeft", atlas, Vector2(1215.0f, 124.0f * 18), Vector2(-129.0f, 124.0f), 9);
		mAnimator->Create(L"MaskedFlyDeathLeft", atlas, Vector2(1215.0f, 124.0f * 19), Vector2(-129.0f, 124.0f), 1);

		mAnimator->Create(L"NoMaskedIdleLeft", atlas, Vector2(1086.0f, 124.0f * 2), Vector2(-129.0f, 124.0f), 1);
		mAnimator->Create(L"NoMaskedMoveLeft", atlas, Vector2(1215.0f, 124.0f * 8), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"NoMaskedFlyLeft", atlas, Vector2(1215.0f, 124.0f * 14), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"NoMaskedHitLeft", atlas, Vector2(1215.0f, 124.0f * 16), Vector2(-129.0f, 124.0f), 6);

		mAnimator->PlayAnimation(L"MaskedMoveRight", true);
		mState = eMaskedState::Idle;

		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		dir = playerPos - monPos;
		dir.Normalize();

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

		switch (mState)
		{
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
		default:
			break;
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
	void MaskedTortoiseScript::move()
	{
		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = GetOwner()->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();
		Transform* atRangeTr = atRange->GetComponent<Transform>();

		if (mbRight)
		{
			monPos.x += mSpeed * Time::DeltaTime();
		}
		else
		{
			monPos.x -= mSpeed * Time::DeltaTime();
		}
		monTr->SetPosition(monPos);
		atRangeTr->SetPosition(monPos);

		mTime += Time::DeltaTime();

		if (mTime > 3.0f)
		{
			mState = eMaskedState::Attack;
			mTime = 0.0f;
			if (mbRight)
			{
				mAnimator->PlayAnimation(L"MaskedAttackRight", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"MaskedAttackLeft", true);
			}
		}
	}
	void MaskedTortoiseScript::attack()
	{
		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = GetOwner()->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();
		Transform* atRangeTr = atRange->GetComponent<Transform>();

		if (mbRight)
		{
			monPos.x += mSpeed * Time::DeltaTime();
		}
		else
		{
			monPos.x -= mSpeed * Time::DeltaTime();
		}
		monTr->SetPosition(monPos);
		atRangeTr->SetPosition(monPos);

		mTime += Time::DeltaTime();
		bool isRange = atRange->GetComponent<AttackRangeScript>()->IsRange();
		
		if (mTime > 0.3f)
		{
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
	void MaskedTortoiseScript::fly()
	{
	}
	void MaskedTortoiseScript::hit()
	{
	}
	void MaskedTortoiseScript::death()
	{
	}
	void MaskedTortoiseScript::pickup()
	{
	}
	void MaskedTortoiseScript::throwHead()
	{
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
			mAnimator->PlayAnimation(L"MaskedIdleRight", true);
			mState = eMaskedState::Idle;
		}
		if (other->GetOwner()->GetName().compare(L"BossRightWall") == 0)
		{
			mAnimator->PlayAnimation(L"MaskedIdleLeft", true);
			mState = eMaskedState::Idle;
		}
		if (other->GetOwner()->GetName().compare(L"PlayerAttack") == 0)
		{
			if (monPos.x < playerPos.x)
			{
				// 왼쪽으로 날아가야함
				mAnimator->PlayAnimation(L"NoMaskedHitLeft", true);
			}
			else
			{
				// 오른쪽으로 날아가야함
				mAnimator->PlayAnimation(L"NoMaskedHitRight", true);
			}
			msHead = object::Instantiate<MaskedHead>(Vector3(monPos), eLayerType::Monster);
			msHead->Initialize();
			mState = eMaskedState::ThrowHead;
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