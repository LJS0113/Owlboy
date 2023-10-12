#pragma once
#include "jsGameObject.h"

namespace js
{
	class Masked : public GameObject
	{
	public:
		Masked();
		~Masked();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:

	};
}
