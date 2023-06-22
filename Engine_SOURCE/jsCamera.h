#pragma once
#include "jsComponent.h"
#include "jsGraphics.h"

namespace js
{
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();

	private:
		static Matrix mView;
		static Matrix mProjection;
	};

}