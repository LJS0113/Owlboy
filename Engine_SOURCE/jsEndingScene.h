#pragma once
#include "jsScene.h"

namespace js
{
	class EndingScene : public Scene
	{
	public:
		EndingScene();
		~EndingScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

	};

}