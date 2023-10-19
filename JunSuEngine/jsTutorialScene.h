#pragma once
#include "..\Engine_SOURCE\jsScene.h"

namespace js
{
	class TutorialScene : public Scene
	{
	public:
		TutorialScene();
		~TutorialScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* player;
	};

}