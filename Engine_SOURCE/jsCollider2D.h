#pragma once
#include "jsComponent.h"
#include "jsTransform.h"

namespace js
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType type) { mType = type; }
		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		Vector3 GetPosition() { return mPosition; }
		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCenter(Vector2 center) { mCenter = center; }
		UINT GetColliderID() { return mColliderID; }

		eColliderOwner GetColliderOwner() { return mColliderOwner; }
		void SetColliderOwner(eColliderOwner colOwner) { mColliderOwner = colOwner; }


	private:
		static UINT mColliderNumber;
		UINT mColliderID;

		eColliderOwner mColliderOwner;
		eColliderType mType;

		Transform* mTransform;

		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;
	};

}