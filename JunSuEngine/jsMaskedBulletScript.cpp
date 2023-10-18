#include "jsMaskedBulletScript.h"
#include "jsResources.h"
#include "jsInput.h"
#include "jsTransform.h"
#include "jsTime.h"
#include "jsGameObject.h"
#include "jsPlayer.h"
#include "jsMeshRenderer.h"


namespace js
{
	MaskedBulletScript::MaskedBulletScript()
	{
	}
	MaskedBulletScript::~MaskedBulletScript()
	{
	}
	void MaskedBulletScript::Initialize()
	{
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"MaskedBulletSprite", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprTortoiseShot_25x17_strip4.png");
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->Create(L"MaskedBullet", atlas, Vector2(0.0f, 0.0f), Vector2(25.0f, 17.0f), 4, Vector2::Zero, 1.0f);
		mAnimator->PlayAnimation(L"MaskedBullet", false);

		Collider2D* cd = GetOwner()->GetComponent<Collider2D>();
		cd->SetSize(Vector2(0.2f, 0.2f));

		Transform* monTr = GetOwner()->GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();
		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		dir = playerPos - monPos;
		dir.Normalize();

		mState = eMaskedBulletState::Shoot;
	}
	void MaskedBulletScript::Update()
	{
		switch (mState)
		{
		case js::MaskedBulletScript::eMaskedBulletState::None:
			none();
			break;
		case js::MaskedBulletScript::eMaskedBulletState::Shoot:
			shoot();
			break;
		case js::MaskedBulletScript::eMaskedBulletState::Hit:
			hit();
			break;
		case js::MaskedBulletScript::eMaskedBulletState::Erase:
			erase();
			break;
		default:
			break;
		}
	}
	void MaskedBulletScript::LateUpdate()
	{
	}
	void MaskedBulletScript::Render()
	{
	}
	void MaskedBulletScript::none()
	{
		mState = eMaskedBulletState::Shoot;
	}
	void MaskedBulletScript::shoot()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 mPos = tr->GetPosition();
		mPos += 3.0f * dir * Time::DeltaTime();
		tr->SetPosition(mPos);

		mLifeTime += Time::DeltaTime();
		if (mLifeTime >= 2.0f)
		{
			if (mbHit)
				mState = eMaskedBulletState::Hit;
			else
				mState = eMaskedBulletState::Erase;
		}
	}
	void MaskedBulletScript::hit()
	{
	}
	void MaskedBulletScript::erase()
	{
		GetOwner()->SetState(GameObject::eState::Dead);
	}
	void MaskedBulletScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void MaskedBulletScript::OnCollisionStay(Collider2D* other)
	{
	}
	void MaskedBulletScript::OnCollisionExit(Collider2D* other)
	{
	}
}