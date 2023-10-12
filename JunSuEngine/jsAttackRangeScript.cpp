#include "jsAttackRangeScript.h"
#include "jsMaskedTortoiseScript.h"
#include "jsPlayer.h"

namespace js
{
	AttackRangeScript::AttackRangeScript()
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
		gPlayer->SetRange(true);
	}
	void AttackRangeScript::OnCollisionStay(Collider2D* other)
	{

	}
	void AttackRangeScript::OnCollisionExit(Collider2D* other)
	{
	}
}