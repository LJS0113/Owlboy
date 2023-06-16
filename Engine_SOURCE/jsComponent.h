#pragma once
#include "jsEntity.h"

namespace js
{
	using namespace js::enums;
	using namespace js::math;

	class GameObject;
	class Component : public Entity
	{ 
	public:
		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		const eComponentType mType;
		GameObject* mOwner;
	};

}