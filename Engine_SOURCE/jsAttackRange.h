#pragma once
#include "jsGameObject.h"


namespace js
{

	class AttackRange : public GameObject
	{
	public:
		AttackRange();
		~AttackRange();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:


	};

}