#include "jsMaskedBullet.h"
#include "..\\JunSuEngine\\\jsBulletScript.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"
#include "..\\JunSuEngine\\\jsMaskedBulletScript.h"


namespace js
{
	MaskedBullet::MaskedBullet()
		: mAnimator(nullptr)
	{
		
	}

	MaskedBullet::~MaskedBullet()
	{
	}

	void MaskedBullet::Initialize()
	{


	}

	void MaskedBullet::Update()
	{
		GameObject::Update();
	}

	void MaskedBullet::Render()
	{
		GameObject::Render();
	}

	void MaskedBullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}

}