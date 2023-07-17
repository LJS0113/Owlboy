#pragma once
#include "..\Engine_SOURCE\jsScript.h"


namespace js
{
	class CloudScript : public Script
	{
	public:
		CloudScript();
		~CloudScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};

}