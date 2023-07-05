#pragma once
#include "..\Engine_SOURCE\jsScene.h"

namespace js
{
	class VellieScene : public Scene
	{
	public:
		VellieScene();
		~VellieScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

	};

}