#include "jsGeddyBullet.h"
#include "..\\JunSuEngine\\\jsBulletScript.h"

namespace js
{
	GeddyBullet::GeddyBullet()
		: mAnimator(nullptr)
	{
		mAnimator = this->AddComponent<Animator>();
		AddComponent<BulletScript>();
		GetComponent<BulletScript>()->Initialize();
	}

	GeddyBullet::~GeddyBullet()
	{
	}

	void GeddyBullet::Initialize()
	{
	}

	void GeddyBullet::Update()
	{
	}

	void GeddyBullet::Render()
	{
	}

	void GeddyBullet::LateUpdate()
	{
	}

}