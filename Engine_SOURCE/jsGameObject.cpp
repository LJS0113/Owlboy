#include "jsGameObject.h"
#include "jsRenderer.h"
#include "jsGraphicDevice_DX11.h"


namespace js
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Initialize()
	{
	}
	void GameObject::Update()
	{
		// ���� ������ ����

	}
	void GameObject::LateUpdate()
	{
	}
	void GameObject::Render()
	{
	}
}