#pragma once
class GeddyArmScript
{
};

#pragma once
#include "..\Engine_SOURCE\jsScript.h"
#include "..\Engine_SOURCE\jsRenderer.h"

namespace js
{
	class GeddyArmScript : public Script
	{
	public:
		enum class eGeddyArmState
		{
			Idle,
			Attack,
		};
		GeddyArmScript();
		~GeddyArmScript();

		virtual void Initialize() override;
		virtual void Update() override;


		virtual void OnCollisionEnter(class Collider2D* other) override;
		virtual void OnCollisionStay(class Collider2D* other) override;
		virtual void OnCollisionExit(class Collider2D* other) override;

		void idle();
		void attack();

	private:
		eGeddyArmState mState;
		class Animator* mAnimator;
		bool mbHang;
		bool mbRight;
		renderer::SpriteReverseCB reverseCB;
		ConstantBuffer* cb;
		Collider2D* cd;
	};

}