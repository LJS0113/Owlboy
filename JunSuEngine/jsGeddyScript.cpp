#include "jsGeddyScript.h"
#include "jsMeshRenderer.h"
#include "jsGameObject.h"
#include "jsResources.h"
#include "jsAnimator.h"
#include "jsGeddyArm.h"
#include "jsObject.h"

namespace js
{
	GeddyScript::GeddyScript()
		:mState(eGeddyState::Idle)
		, mbRight(true)
		, mbHang(false)
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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 geddyPos = tr->GetPosition();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GeddySprite", L"..\\Resources\\Texture\\Geddy.png");
		mAnimator->Create(L"GeddyIdleRight", atlas, Vector2(0.0f, 72.636f * 6), Vector2(64.0f, 72.636f), 13);
		mAnimator->Create(L"GeddyHangRight", atlas, Vector2(0.0f, 72.636f * 1), Vector2(64.0f, 72.636f), 5);
		mAnimator->Create(L"GeddyFallRight", atlas, Vector2(0.0f, 72.636f * 5), Vector2(64.0f, 72.636f), 3);

		mAnimator->Create(L"GeddyIdleLeft", atlas, Vector2(896.0f, 72.636f * 6), Vector2(-64.0f, 72.636f), 13);
		mAnimator->Create(L"GeddyHangLeft", atlas, Vector2(896.0f, 72.636f * 1), Vector2(-64.0f, 72.636f), 5);
		mAnimator->Create(L"GeddyFallLeft", atlas, Vector2(896.0f, 72.636f * 5), Vector2(-64.0f, 72.636f), 3);



		mAnimator->PlayAnimation(L"GeddyIdleRight", true);
		mState = eGeddyState::Idle;
	}

	void GeddyScript::Update()
	{
		//if (mbRight)
		//{
		//	// 오른쪽이면 0, 왼쪽이면 1
		//	reverseCB.reverse = 0;

		//	cb = renderer::constantBuffer[(UINT)eCBType::Reverse];
		//	cb->SetData(&reverseCB);
		//	cb->Bind(eShaderStage::PS);
		//}
		//else
		//{
		//	// 오른쪽이면 0, 왼쪽이면 1
		//	reverseCB.reverse = 1;

		//	cb = renderer::constantBuffer[(UINT)eCBType::Reverse];
		//	cb->SetData(&reverseCB);
		//	cb->Bind(eShaderStage::PS);
		//}

		switch (mState)
		{
		case js::GeddyScript::eGeddyState::Idle:
			idle();
			break;
		case js::GeddyScript::eGeddyState::Attack:
			attack();
			break;
		case js::GeddyScript::eGeddyState::Hang:
			hang();
			break;
		case js::GeddyScript::eGeddyState::Death:
			death();
			break;
		case js::GeddyScript::eGeddyState::Fall:
			fall();
			break;
		default:
			break;
		}
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

	void GeddyScript::idle()
	{

	}

	void GeddyScript::attack()
	{
	}

	void GeddyScript::death()
	{
	}

	void GeddyScript::hang()
	{
	}

	void GeddyScript::fall()
	{
	}

}