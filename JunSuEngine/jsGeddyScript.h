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
			Idle,
			Move,
			Attack,
			Hang,
			Fall,
			Death,
		};
		GeddyScript();
		~GeddyScript();

		virtual void Initialize() override;
		virtual void Update() override;


		virtual void OnCollisionEnter(class Collider2D* other) override;
		virtual void OnCollisionStay(class Collider2D* other) override;
		virtual void OnCollisionExit(class Collider2D* other) override;

		void idle();
		void move();
		void attack();
		void death();
		void hang();
		void fall();

	private:
		eGeddyState mState;
		class Animator* mAnimator;
		bool mbHang;
		bool mbRight;
		renderer::SpriteReverseCB reverseCB;
		ConstantBuffer* cb;
		Collider2D* cd;
		class GeddyBullet* bullet;
	};

}