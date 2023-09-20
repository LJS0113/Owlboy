#include "jsGeddyBullet.h"
#include "..\\JunSuEngine\\\jsBulletScript.h"

namespace js
{
	GeddyBullet::GeddyBullet()
		: mAnimator(nullptr)
	{
		mAnimator = this->AddComponent<Animator>();
	}

	GeddyBullet::~GeddyBullet()
	{
	}

	void GeddyBullet::Initialize()
	{
	}

	void GeddyBullet::Update()
	{
		GameObject::Update();
	}

	void GeddyBullet::Render()
	{
		GameObject::Render();
	}

	void GeddyBullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}

}