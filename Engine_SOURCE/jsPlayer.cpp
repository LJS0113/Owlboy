#include "jsPlayer.h"
#include "jsTransform.h"

namespace js
{
	Player* gPlayer = nullptr;

	Player::Player()
		: mbInRange(false)
	{
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}

}