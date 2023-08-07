#pragma once
#include "jsComputeShader.h"
#include "jsStructedBuffer.h"


namespace js::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetParticleBuffer(StructedBuffer* particleBuffer);

	private:
		StructedBuffer* mParticleBuffer;
	};

}