#pragma once
#include "jsGameObject.h"


namespace js
{

	class MouseCursor : public GameObject
	{
	public:
		MouseCursor();
		~MouseCursor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:


	};
}