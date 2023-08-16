#pragma once
#include "jsGameObject.h"


namespace js
{

	class Door : public GameObject
	{
	public:
		Door();
		~Door();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:


	};

}