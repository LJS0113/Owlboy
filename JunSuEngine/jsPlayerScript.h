#pragma once
#include "..\Engine_SOURCE\jsScript.h"


namespace js
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();

	private:
	};

}