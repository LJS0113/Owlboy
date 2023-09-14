#pragma once
#include "jsComponent.h"

namespace js
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force);
		void SetGround(bool ground) { mbGround = ground; }
		bool GetGround() { return mbGround; }
		void SetWall(bool wall) { mbWall = wall; }
		bool GetWall() { return mbWall; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 GetVelocity() { return mVelocity; }

	private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;

		Vector2 mGravity; 
		float mFriction;
		bool mbGround;
		bool mbWall;
		float mGravityAccel;
		float mSpeed;


		/*float mStaticFriction;
		float mKineticFriction;*/
		//float mCoefficientFriction;
		//float mNormalForce;
	};
}
