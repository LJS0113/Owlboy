#include "jsBulletScript.h"
#include "jsGameObject.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"


namespace js
{
	BulletScript::BulletScript()
		: mAnimator(nullptr)
	{
	}
	BulletScript::~BulletScript()
	{
	}
	void BulletScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		mAnimator = GetOwner()->GetComponent<Animator>();
		Collider2D* cd = GetOwner()->GetComponent<Collider2D>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 geddyPos = tr->GetPosition();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GeddyBulletSprite", L"..\\Resources\\Texture\\mechanicBullet.png");
		mAnimator->Create(L"GeddyBullet", atlas, Vector2(0.0f, 0.0f), Vector2(33.0f, 13.0f), 8);

		mAnimator->PlayAnimation(L"GeddyBullet", false);
	}
	void BulletScript::Update()
	{
	}
	void BulletScript::LateUpdate()
	{
	}
	void BulletScript::Render()
	{
	}
	void BulletScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void BulletScript::OnCollisionStay(Collider2D* other)
	{
	}
	void BulletScript::OnCollisionExit(Collider2D* other)
	{
	}
}