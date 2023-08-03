#pragma once
#include "jsResource.h"
#include "jsGraphicDevice_DX11.h"

namespace js
{
	using namespace graphics;

	class Mesh : public Resource
	{
	public:
		Mesh();
		~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* data, UINT count);
		bool CreateIndexBuffer(void* data, UINT count);

		void BindBuffer(); // Buffer 파이프라인에 묶어준다.
		void Render();
		void RenderInstanced(UINT startIndexLocation);

		UINT GetIndexCount() { return mIndexCount; }

		void SetRadius(float radius) { mRadius = radius; }
		float GetRadius() { return mRadius; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;

		D3D11_BUFFER_DESC mVBDesc;
		D3D11_BUFFER_DESC mIBDesc;

		UINT mIndexCount;
		float mRadius;
	};

}