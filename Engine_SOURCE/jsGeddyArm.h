#pragma once
#include "jsGameObject.h"

namespace js
{
	class GeddyArm : public GameObject
	{
	public:
		GeddyArm();
		~GeddyArm();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:
	};
}
