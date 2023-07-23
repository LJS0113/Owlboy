#pragma once
#include "..\Engine_SOURCE\jsScript.h"


namespace js
{
	class PlayerScript : public Script
	{
	public:
		enum class ePlayerState
		{
			None,
			Idle,
			Move,
			Attack,
			Death,
			Dash,
			Jump,
		};
		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();

		virtual void OnCollisionEnter(class Collider2D* other) override;
		virtual void OnCollisionStay(class Collider2D* other) override;
		virtual void OnCollisionExit(class Collider2D* other) override;

		void move();
		void idle();
		void dash();
		void jump();
		void attack();
		void death();

	private:
		ePlayerState mState;
		class Animator* mAnimator;
	};

}