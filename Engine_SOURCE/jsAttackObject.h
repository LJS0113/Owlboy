#pragma once
#include "jsGameObject.h"


namespace js
{

	class AttackObject : public GameObject
	{
	public:
		AttackObject();
		~AttackObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:
		class Collider2D* cd;


	};

}