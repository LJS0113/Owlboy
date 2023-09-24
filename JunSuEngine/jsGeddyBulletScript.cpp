#include "jsGeddyBulletScript.h"
#include "jsGameObject.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"
#include "jsInput.h"
#include "jsTime.h"

namespace js
{
	GeddyBulletScript::GeddyBulletScript()
		: mbHit(false)
		, mLifeTime(0.0f)
	{
	}
	GeddyBulletScript::~GeddyBulletScript()
	{
	}
	void GeddyBulletScript::Initialize()
	{
		//MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		mAnimator = GetOwner()->GetComponent<Animator>();
		Collider2D* cd = GetOwner()->GetComponent<Collider2D>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 geddyPos = tr->GetPosition();
		tr->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		cd->SetSize(Vector2(0.1f, 0.1f));
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GeddyBulletSprite", L"..\\Resources\\Texture\\mechanicBullet.png");
		mAnimator->Create(L"GeddyBullet", atlas, Vector2(0.0f, 0.0f), Vector2(13.0f, 13.0f), 8);

		mAnimator->PlayAnimation(L"GeddyBullet", true);
		mState = eGeddyBulletState::Shoot;
	}
	void GeddyBulletScript::Update()
	{
		switch (mState)
		{
		case js::GeddyBulletScript::eGeddyBulletState::None:
			none();
			break;
		case js::GeddyBulletScript::eGeddyBulletState::Shoot:
			shoot();
			break;
		case js::GeddyBulletScript::eGeddyBulletState::Hit:
			hit();
			break;
		case js::GeddyBulletScript::eGeddyBulletState::Erase:
			erase();
			break;
		default:
			break;
		}
	}
	void GeddyBulletScript::LateUpdate()
	{
	}
	void GeddyBulletScript::Render()
	{
	}

	void GeddyBulletScript::none()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
			mState = eGeddyBulletState::Shoot;
	}

	void GeddyBulletScript::shoot()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 mPos = tr->GetPosition();
		Vector2 pos = Input::GetMousePos();
		Vector3 mousePos = Vector3(pos.x, pos.y, 0.0f);
		mousePos = tr->GetNDCPos(Vector3(mousePos.x, mousePos.y, mousePos.z));
		Vector3 dir = mousePos - mPos;
		dir.Normalize();
		// position += direction * speed * time
		//mPos.y += 4.0f * Time::DeltaTime();
		mPos += 4.0f * dir * Time::DeltaTime();
		tr->SetPosition(mPos);
		mLifeTime += Time::DeltaTime();
		if (mLifeTime >= 1.5f)
		{
			if (mbHit)
				mState = eGeddyBulletState::Hit;
			else
				mState = eGeddyBulletState::Erase;
		}
	}

	void GeddyBulletScript::hit()
	{
	}

	void GeddyBulletScript::erase()
	{
		GetOwner()->SetState(GameObject::eState::Dead);
	}


	void GeddyBulletScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void GeddyBulletScript::OnCollisionStay(Collider2D* other)
	{
	}
	void GeddyBulletScript::OnCollisionExit(Collider2D* other)
	{
	}
}