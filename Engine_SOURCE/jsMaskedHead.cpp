#include "jsMaskedHead.h"
#include "jsMeshRenderer.h"
#include "jsGameObject.h"
#include "jsResources.h"
#include "jsTime.h"

namespace js
{
	MaskedHead::MaskedHead()
		: mbRight(false)
	{

	}
	MaskedHead::~MaskedHead()
	{
	}
	void MaskedHead::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MonsterAnimationMaterial"));
		mAnimator =AddComponent<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"MaskedTortoiseSprite", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprMask_129x124_strip8.png");
		mAnimator->Create(L"FlyingMaskRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 8, Vector2::Zero, 1.0f);
		mAnimator->Create(L"FlyingMaskLeft", atlas, Vector2(903, 0.0f), Vector2(-129.0f, 124.0f), 8, Vector2::Zero, 1.0f);
		
		atlas = Resources::Load<Texture>(L"MaskedTortoiseSprite", L"..\\Resources\\Texture\\Monster\\Masked_Tortoise\\sprLand_strip9.png");
		mAnimator->Create(L"RandingMaskRight", atlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), 9, Vector2::Zero, 1.0f);
		mAnimator->Create(L"RandingMaskLeft", atlas, Vector2(1032.0f, 0.0f), Vector2(-129.0f, 124.0f), 9, Vector2::Zero, 1.0f);
		mAnimator->PlayAnimation(L"FlyingMaskRight", false);
		cd = AddComponent<Collider2D>();
		cd->SetSize(Vector2(0.5f, 0.5f));
		cd->SetCenter(Vector2(0.0f, 0.0f));
	}
	void MaskedHead::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		if (mAnimator->IsComplete())
		{

		}
		else
		{
			pos.x -= 2.0f * Time::DeltaTime();
		}



		GameObject::Update();

	}
	void MaskedHead::Render()
	{
		GameObject::Render();
	}
	void MaskedHead::LateUpdate()
	{
		GameObject::LateUpdate();
	}
}