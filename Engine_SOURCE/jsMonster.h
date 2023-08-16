#pragma once
#include "jsGameObject.h"

namespace js
{
	class Monster : public GameObject
	{
	public:
		Monster();
		~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:

	};
}
