#pragma once
#include "jsComponent.h"


namespace js
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetRotation(Vector3 rotation) { mRotation = rotation; }
		void SetScale(Vector3 scale) { mScale = scale; }

		void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }

		Vector3 GetPosition() { return mPosition; }
		Vector3 GetRotation() { return mRotation; }
		Vector3 GetScale() { return mScale; }

		Vector3 Foward() { return mFoward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		void SetParent(Transform* transform) { mParent = transform; }
		Transform* GetParent() { return mParent; }
		static Vector3 GetWorldPos(Vector3 pos);
		static Vector3 GetNDCPos(Vector3 pos);
		Matrix& GetMatrix() { return mWorld; }

	private:
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		Vector3 mUp;
		Vector3 mFoward;
		Vector3 mRight;

		Matrix mWorld;

		Transform* mParent;
	};

}