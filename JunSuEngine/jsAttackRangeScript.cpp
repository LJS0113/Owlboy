#include "jsAttackRangeScript.h"
#include "jsMaskedTortoiseScript.h"
#include "jsPlayer.h"
#include "jsGameObject.h"
#include "jsComponent.h"

namespace js
{
	AttackRangeScript::AttackRangeScript()
		: mbRange(false)
	{
	}
	AttackRangeScript::~AttackRangeScript()
	{
	}
	void AttackRangeScript::Initialize()
	{
	}
	void AttackRangeScript::Update()
	{
	}
	void AttackRangeScript::LateUpdate()
	{
	}
	void AttackRangeScript::Render()
	{

	}
	void AttackRangeScript::OnCollisionEnter(Collider2D* other)
	{
		mbRange = true;
	}
	void AttackRangeScript::OnCollisionStay(Collider2D* other)
	{

	}
	void AttackRangeScript::OnCollisionExit(Collider2D* other)
	{
		mbRange = false;
	}
}