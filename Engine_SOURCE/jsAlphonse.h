#pragma once
#include "jsGameObject.h"

namespace js
{
	class Alphonse : public GameObject
	{
	public:
		Alphonse();
		~Alphonse();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:
	};
}
