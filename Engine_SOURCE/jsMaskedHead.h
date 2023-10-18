#pragma once
#include "jsGameObject.h"
#include "jsAnimator.h"

namespace js
{
	class MaskedHead : public GameObject
	{
	public:
		MaskedHead();
		~MaskedHead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

		void SetRightDir(bool right) { mbRight = right; }

	private:
		Animator* mAnimator;
		class Collider2D* cd;

		bool mbRight;
	};
}
