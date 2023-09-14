#pragma once
#include "jsGameObject.h"

namespace js
{
	class Wall : public GameObject
	{
	public:
		Wall();
		virtual ~Wall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;


	private:
	};
}

