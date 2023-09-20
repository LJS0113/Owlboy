#pragma once
#include "..\Engine_SOURCE\jsScript.h"
#include "jsAnimator.h"

namespace js
{
	class GeddyBulletScript : public Script
	{
	public:
		enum class eGeddyBulletState
		{
			None,
			Shoot, 
			Hit,
			Erase,
		};
		GeddyBulletScript();
		~GeddyBulletScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void none();
		void shoot();
		void hit();
		void erase();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:
		Animator* mAnimator;
		eGeddyBulletState mState;
		bool mbHit;

		float mLifeTime;
	};
}