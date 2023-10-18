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

		void SetRange(bool range) { mbRange = range; }
		bool GetRange() { return mbRange; }

	private:
		bool mbRange;

	};

}