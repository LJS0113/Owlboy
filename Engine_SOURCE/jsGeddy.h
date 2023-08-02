#pragma once
#include "jsGameObject.h"

namespace js
{
	class Geddy : public GameObject
	{
	public:
		Geddy();
		~Geddy();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:
	};
}
