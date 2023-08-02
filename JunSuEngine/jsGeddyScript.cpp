#include "jsGeddyScript.h"
#include "jsMeshRenderer.h"
#include "jsGameObject.h"
#include "jsResources.h"
#include "jsAnimator.h"


namespace js
{
	GeddyScript::GeddyScript()
	{
	}

	GeddyScript::~GeddyScript()
	{
	}

	void GeddyScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		mAnimator = GetOwner()->AddComponent<Animator>();
		cd = GetOwner()->GetComponent<Collider2D>();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GeddySprite", L"..\\Resources\\Texture\\Geddy.png");
		mAnimator->Create(L"GeddyIdleRight", atlas, Vector2(0.0f, 72.636f * 6), Vector2(64.0f, 72.636f), 13);
		mAnimator->Create(L"GeddyHangRight", atlas, Vector2(0.0f, 72.636f * 1), Vector2(64.0f, 72.636f), 5);

		mAnimator->PlayAnimation(L"GeddyIdleRight", true);
	}

	void GeddyScript::Update()
	{
	}

	void GeddyScript::OnCollisionEnter(Collider2D* other)
	{
	}

	void GeddyScript::OnCollisionStay(Collider2D* other)
	{
	}

	void GeddyScript::OnCollisionExit(Collider2D* other)
	{
	}

	void GeddyScript::move()
	{
	}

	void GeddyScript::idle()
	{
	}

	void GeddyScript::jump()
	{
	}

	void GeddyScript::attack()
	{
	}

	void GeddyScript::death()
	{
	}

	void GeddyScript::fly()
	{
	}

}