#pragma once
#include "..\\Engine_SOURCE\\jsGameObject.h"

namespace gui
{
	class EditorObject : public js::GameObject
	{
	public:
		EditorObject();
		~EditorObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};

}