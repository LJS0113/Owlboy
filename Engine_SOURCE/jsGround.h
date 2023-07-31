#pragma once
#include "jsGameObject.h"

namespace js
{
	class Ground : public GameObject
	{
	public:
		Ground();
		virtual ~Ground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

		virtual void OnCollisionEnter(class Collider2D* other);
		virtual void OnCollisionStay(class Collider2D* other);
		virtual void OnCollisionExit(class Collider2D* other);

		void SetPlayer(class GameObject* player) { mPlayer = player; }

	private:
		class Collider2D* mCollider;
		class GameObject* mPlayer;
	};
}

