#pragma once
#include "jsComputeShader.h"


namespace js::graphics
{
	class PaintShader : public ComputeShader
	{
	public:
		PaintShader();
		~PaintShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetTarget(std::shared_ptr<class Texture> target) { mTarget = target; }

	private:
		std::shared_ptr<class Texture> mTarget;

	};

}