#pragma once
#include "..\Engine_SOURCE\jsScript.h"
#include "..\Engine_SOURCE\jsRenderer.h"

namespace js
{
	class GeddyScript : public Script
	{
	public:
		enum class eGeddyState
		{
			None,
			Idle,
			Move,
			Attack,
			Death,
			Fly,
		};
		GeddyScript();
		~GeddyScript();

		virtual void Initialize() override;
		virtual void Update() override;


		virtual void OnCollisionEnter(class Collider2D* other) override;
		virtual void OnCollisionStay(class Collider2D* other) override;
		virtual void OnCollisionExit(class Collider2D* other) override;

		void move();
		void idle();
		void jump();
		void attack();
		void death();
		void fly();

	private:
		eGeddyState mState;
		class Animator* mAnimator;
		bool mbFly;
		bool mbRight;
		renderer::SpriteReverseCB reverseCB;
		ConstantBuffer* cb;
		Collider2D* cd;
	};

}