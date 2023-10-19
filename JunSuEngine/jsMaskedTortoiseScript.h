#pragma once
#include "..\Engine_SOURCE\jsScript.h"
#include "..\Engine_SOURCE\jsRenderer.h"

namespace js
{
	class MaskedTortoiseScript : public Script
	{
	public:
		enum class eMaskedState
		{
			Wait,
			Idle,
			Move,
			Attack,
			Fly,
			Hit,
			ThrowHead,
			PickUp,
			Death,
			Disappear,
		};
		MaskedTortoiseScript();
		~MaskedTortoiseScript();

		virtual void Initialize() override;
		virtual void Update() override;


		virtual void OnCollisionEnter(class Collider2D* other) override;
		virtual void OnCollisionStay(class Collider2D* other) override;
		virtual void OnCollisionExit(class Collider2D* other) override;

		void wait();
		void idle();
		void move();
		void attack();
		void fly();
		void hit();
		void death();
		void pickup();
		void throwHead();
		void disappear();

		void SetRange(bool range) { mbRange = range; }
		bool GetRange() { return mbRange; }

	private:
		eMaskedState mState;
		class Animator* mAnimator;
		renderer::MonsterReverseCB reverseCB;
		float mSpeed;
		float mTime;
		float deathTime;
		UINT atCount;
		Vector3 dir;
		class AttackRange* atRange;
		class MaskedHead* msHead;
		//class MaskedBullet* msBullet;
		float hp;
		renderer::CollisionCB collisionCB;
		ConstantBuffer* collisionCb;
		ConstantBuffer* reverseCb;
		ConstantBuffer* cb;

		Collider2D* cd;
		Collider2D* rangeCd;
		bool mbFly;
		bool mbRange;
		bool mbRight;
		bool mbTouch;
		bool mbHead;
	};

}