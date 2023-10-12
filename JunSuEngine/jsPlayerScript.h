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
			Hang,
			Death,
			Dash,
			Jump,
			Fall,
			Fly,
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
		void hang();
		void attack();
		void death();
		void fly();
		void fall();

		ePlayerState GetState() { return mState; }
		bool GetRightDir() { return mbRight; }
		bool GetSummon() { return mbSummon; }
		bool IsHang() { return mbHang; }
		void SetSpeed(float speed) { mSpeed = speed; }
		float GetSpeed() { return mSpeed; }

	private:
		ePlayerState mState;
		class Animator* mAnimator;
		bool mbFly;
		bool mbRight;
		bool mbHang;
		bool mbSummon;
		Collider2D* cd;
		float mSpeed;
		renderer::SpriteReverseCB reverseCB;
		renderer::CollisionCB collisionCB;
		ConstantBuffer* collisionCb;
		ConstantBuffer* reverseCb;
	};
}