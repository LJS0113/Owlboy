#pragma once
#include "..\Engine_SOURCE\jsScript.h"
#include "jsAnimator.h"

namespace js
{
	class MaskedHeadScript : public Script
	{
	public:
		enum class eMaskedHeadState
		{
			Fly,
			Rand,
			PickUp,
		};

		MaskedHeadScript();
		~MaskedHeadScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void fly();
		void rand();
		void pickup();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetRightDir(bool right) { mbRight = right; }

	private:
		Animator* mAnimator;
		eMaskedHeadState mState;
		bool mbRight;
		float mSpeed;
	};
}