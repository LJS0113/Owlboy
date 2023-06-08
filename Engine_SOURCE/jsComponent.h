#pragma once
#include "jsEntity.h"

namespace js
{
	using namespace js::enums;
	class Component : public Entity
	{ 
	public:
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();


	private:
		const eComponentType mType;
	};

}