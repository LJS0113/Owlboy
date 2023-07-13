#pragma once
#include "..\\Engine_SOURCE\\jsGameObject.h"

namespace gui
{
	class DebugObject : public js::GameObject
	{
	public:
		DebugObject();
		~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:


	};

}