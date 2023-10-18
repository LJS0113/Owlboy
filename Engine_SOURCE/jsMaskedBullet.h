#pragma once
#include "jsGameObject.h"
#include "jsAnimator.h"

namespace js
{
	class MaskedBullet : public GameObject
	{
	public:
		MaskedBullet();
		~MaskedBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:
		Animator* mAnimator;
	};
}
