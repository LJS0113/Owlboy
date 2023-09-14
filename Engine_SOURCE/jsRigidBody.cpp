#include "jsRigidbody.h"
#include "jsTime.h"
#include "jsGameObject.h"
#include "jsTransform.h"


namespace js
{

	Rigidbody::Rigidbody()
		: Component(eComponentType::RigidBody)
		, mMass(0.0f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 1000.0f;
		mbGround = false;
		mbWall = false;
		mGravity = Vector2(0.0f, -3.0f);
		mFriction = 100.0f;
	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Initialize()
	{

	}

	void Rigidbody::Update()
	{
		//// F = M * A
		//// A = M / F
		//mAccelation = mForce / mMass;

		//// �ӵ��� ���ӵ��� �����ش�.
		//mVelocity += mAccelation * Time::DeltaTime();

		//if (mbGround)
		//{
		//	// ������ ������
		//	Vector2 gravity = mGravity;
		//	gravity.Normalize();
		//	float dot = mVelocity.Dot(gravity);
		//	mVelocity -= gravity * dot;
		//}
		//else
		//{
		//	mVelocity += mGravity * Time::DeltaTime();
		//}

		//// �߷°��ӵ� �ִ� �ӵ� ����
		//Vector2 gravity = mGravity;
		//gravity.Normalize();
		//float dot = mVelocity.Dot(gravity);
		//gravity = gravity * dot;

		//Vector2 sideVelocity = mVelocity - gravity;
		//if (mLimitedVelocity.y < gravity.Length())
		//{
		//	gravity.Normalize();
		//	gravity *= mLimitedVelocity.y;
		//}

		//if (mLimitedVelocity.x < sideVelocity.Length())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= mLimitedVelocity.x;
		//}

		//// �ӵ��� �°Բ� ��ü�� �̵���Ų��.
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();
		//pos = pos + mVelocity * Time::DeltaTime();
		//tr->SetPosition(pos);
		//mForce = Vector2::Zero;


		// �� ���� ���� ��
		if (mbGround)
		{
			mVelocity.y = 0.0f;
		}
		// ���߿� �� ���� ��
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);
	}

	void Rigidbody::LateUpdate()
	{
	}

	void Rigidbody::Render()
	{
	}

	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}
