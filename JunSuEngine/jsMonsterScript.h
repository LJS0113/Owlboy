#pragma once
#include "..\Engine_SOURCE\jsScript.h"


namespace js
{
	class MonsterScript : public Script
	{
	public:
		MonsterScript();
		~MonsterScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};

}