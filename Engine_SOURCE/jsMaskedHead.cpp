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
	}
	void MaskedHead::Update()
	{
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