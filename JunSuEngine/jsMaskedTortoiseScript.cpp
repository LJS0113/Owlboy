#include "jsMaskedTortoiseScript.h"
#include "jsAnimator.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"
#include "jsGameObject.h"


namespace js
{
	MaskedTortoiseScript::MaskedTortoiseScript()
	{
	}
	MaskedTortoiseScript::~MaskedTortoiseScript()
	{
	}
	void MaskedTortoiseScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		mAnimator = GetOwner()->AddComponent<Animator>();
		cd = GetOwner()->GetComponent<Collider2D>();

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
		mAnimator->Create(L"FlyingMask", atlas, Vector2(0.0f, 124.0f * 17), Vector2(129.0f, 124.0f), 8);
		mAnimator->Create(L"RandingMask", atlas, Vector2(0.0f, 124.0f * 18), Vector2(129.0f, 124.0f), 9);
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
		mAnimator->Create(L"FlyingMask", atlas, Vector2(1215.0f, 124.0f * 17), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"RandingMask", atlas, Vector2(1215.0f, 124.0f * 18), Vector2(-129.0f, 124.0f), 9);
		mAnimator->Create(L"MaskedFlyDeathLeft", atlas, Vector2(1215.0f, 124.0f * 19), Vector2(-129.0f, 124.0f), 1);

		mAnimator->Create(L"NoMaskedIdleLeft", atlas, Vector2(1086.0f, 124.0f * 2), Vector2(-129.0f, 124.0f), 1);
		mAnimator->Create(L"NoMaskedMoveLeft", atlas, Vector2(1215.0f, 124.0f * 8), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"NoMaskedFlyLeft", atlas, Vector2(1215.0f, 124.0f * 14), Vector2(-129.0f, 124.0f), 8);
		mAnimator->Create(L"NoMaskedHitLeft", atlas, Vector2(1215.0f, 124.0f * 16), Vector2(-129.0f, 124.0f), 6);


		mAnimator->PlayAnimation(L"MaskedMoveRight", true);
	}
	void MaskedTortoiseScript::Update()
	{
	}
	void MaskedTortoiseScript::idle()
	{
	}
	void MaskedTortoiseScript::move()
	{
	}
	void MaskedTortoiseScript::attack()
	{
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
	void MaskedTortoiseScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void MaskedTortoiseScript::OnCollisionStay(Collider2D* other)
	{
	}
	void MaskedTortoiseScript::OnCollisionExit(Collider2D* other)
	{
	}
}