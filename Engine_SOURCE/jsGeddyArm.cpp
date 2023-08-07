#include "jsGeddyArm.h"
#include "jsResources.h"

namespace js
{
	GeddyArm::GeddyArm()
		:mAnimator(nullptr)
	{
		mAnimator = this->AddComponent<Animator>();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GeddyArmSprite", L"..\\Resources\\Texture\\mechanic_arm.png");
		mAnimator->Create(L"GeddyArmRight", atlas, Vector2(0.0f, 0.0f), Vector2(48.0f, 64.0f), 5);
		mAnimator->Create(L"GeddyArmDownRight", atlas, Vector2(0.0f, 64.0f), Vector2(48.0f, 64.0f), 5);

		mAnimator->Create(L"GeddyArmLeft", atlas, Vector2(192.0f, 0.0f), Vector2(-48.0f, 64.0f), 5);
		mAnimator->Create(L"GeddyArmDownLeft", atlas, Vector2(192.0f, 64.0f), Vector2(-48.0f, 64.0f), 5);

		mAnimator->PlayAnimation(L"GeddyArmRight", true);
	}
	GeddyArm::~GeddyArm()
	{
	}
	void GeddyArm::Initialize()
	{
		GameObject::Initialize();

	}
	void GeddyArm::Update()
	{
		GameObject::Update();
	}
	void GeddyArm::Render()
	{
		GameObject::Render();
	}
	void GeddyArm::LateUpdate()
	{
		GameObject::LateUpdate();
	}
}