#include "jsMaskedHeadScript.h"
#include "jsMeshRenderer.h"
#include "jsGameObject.h"
#include "jsResources.h"
#include "jsTime.h"
#include "jsRigidBody.h"


namespace js
{
	MaskedHeadScript::MaskedHeadScript()
		: mbRight(false)
		, mSpeed(5.0f)
	{
	}
	MaskedHeadScript::~MaskedHeadScript()
	{
	}
	void MaskedHeadScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		mAnimator = GetOwner()->GetComponent<Animator>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(1.5f, 1.5f, 1.0f));
		Collider2D* cd = GetOwner()->GetComponent<Collider2D>();
		cd->SetSize(Vector2(0.5f, 0.5f));
		cd->SetCenter(Vector2(0.0f, 0.0f));
		Rigidbody* rb = GetOwner()->AddComponent<Rigidbody>();
		
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"MaskedHeadSpriteFly", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprMask_129x124_strip8.png");
		mAnimator->Create(L"FlyingMaskRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 8);
		
		atlas = Resources::Load<Texture>(L"MaskedHeadSpriteLand", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprLand_strip9.png");
		mAnimator->Create(L"RandingMaskRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 9);
		
		mAnimator->PlayAnimation(L"FlyingMaskRight", false);
		mState = eMaskedHeadState::Fly;
	}
	void MaskedHeadScript::Update()
	{
		switch (mState)
		{
		case js::MaskedHeadScript::eMaskedHeadState::Fly:
			fly();
			break;
		case js::MaskedHeadScript::eMaskedHeadState::Rand:
			rand();
			break;
		case js::MaskedHeadScript::eMaskedHeadState::PickUp:
			pickup();
			break;
		default:
			break;
		}
	}
	void MaskedHeadScript::LateUpdate()
	{
	}
	void MaskedHeadScript::Render()
	{
	}
	void MaskedHeadScript::fly()
	{
		Transform* headTr = GetOwner()->GetComponent<Transform>();
		Vector3 headPos = headTr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		if (mbRight)
		{
			headPos.x += mSpeed * Time::DeltaTime();
		}
		else
		{
			headPos.x -= mSpeed * Time::DeltaTime();
		}

		if (rb->GetGround())
		{
			mState = eMaskedHeadState::Rand;
			mAnimator->PlayAnimation(L"RandingMaskRight", false);
		}

		headTr->SetPosition(headPos);
	}
	void MaskedHeadScript::rand()
	{

	}
	void MaskedHeadScript::pickup()
	{
	}
	void MaskedHeadScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetOwner()->GetName().compare(L"BossLeftWall") == 0)
		{
			mSpeed = 0.0f;
		}
		if (other->GetOwner()->GetName().compare(L"BossRightWall") == 0)
		{
			mSpeed = 0.0f;
		}
	}
	void MaskedHeadScript::OnCollisionStay(Collider2D* other)
	{
	}
	void MaskedHeadScript::OnCollisionExit(Collider2D* other)
	{
	}
}