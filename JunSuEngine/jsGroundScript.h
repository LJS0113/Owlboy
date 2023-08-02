#pragma once
#include "..\Engine_SOURCE\jsScript.h"


namespace js
{
	class GroundScript : public Script
	{
	public:
		GroundScript();
		~GroundScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		//void SetPlayer(class GameObject* player) { mPlayer = player; }

	private:


	};
}