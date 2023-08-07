#pragma once
#include "jsGameObject.h"

namespace js
{
	class GeddyBullet : public GameObject
	{
	public:
		GeddyBullet();
		~GeddyBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:
	};
}
