#pragma once
#include "jsEntity.h"
#include "jsGraphics.h"

namespace js::graphics
{

	class StructedBuffer : public GpuBuffer
	{
	public:
		StructedBuffer();
		~StructedBuffer();

		bool Create(UINT size, UINT stride, eSRVTpye type);
		void SetData(void* data, UINT stride);
		void Bind(eShaderStage stage, UINT slot);

		UINT GetSize() { return mSize; }
		UINT GetStride() { return mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		eSRVTpye mType;

		UINT mSize;
		UINT mStride;

	};

}