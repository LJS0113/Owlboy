#pragma once
#include "jsGameObject.h"

namespace js
{
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

		void SetRange(bool range) { mbInRange = range; }
		bool GetRange() { return mbInRange; }

	private:
		bool mbInRange;

	};
	extern Player* gPlayer;
}
