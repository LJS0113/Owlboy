#include "jsMesh.h"
#include "jsRenderer.h"

namespace js
{
	Mesh::Mesh()
		: Resource(enums::eResourceType::Mesh)
		, mVertexBuffer(nullptr)
		, mIndexBuffer(nullptr)
		, mVBDesc{}
		, mIBDesc{}
		, mIndexCount(0)
	{
	}
	Mesh::~Mesh()
	{
	}
	HRESULT Mesh::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	bool Mesh::CreateVertexBuffer(void* data, UINT count)
	{
		mVBDesc.ByteWidth = sizeof(renderer::Vertex) * count; // ���� ũ��, ���� �츮�� ���� Vertex struct�� �� 12���� �����̹Ƿ� ��12
		mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // ���� ���۷� ����� ���̳ĸ� ����.
		mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mVBDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sub = {}; // �����͸� �ѱ涩 �ٷ� �ѱ�°� �ƴ϶� ���긮�ҽ��� ��� �����ش�.
		sub.pSysMem = data;

		if (!GetDevice()->CreateBuffer(mVertexBuffer.GetAddressOf(), &mVBDesc, &sub))
			return false;

		return true;
	}
	bool Mesh::CreateIndexBuffer(void* data, UINT count)
	{
		mIndexCount = count;
		mIBDesc.ByteWidth = sizeof(UINT) * count; // ���� ũ��, ���� �츮�� ���� Vertex struct�� �� 12���� �����̹Ƿ� ��12
		mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER; // ���� ���۷� ����� ���̳ĸ� ����.
		mIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mIBDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sub = {}; // �����͸� �ѱ涩 �ٷ� �ѱ�°� �ƴ϶� ���긮�ҽ��� ��� �����ش�.
		sub.pSysMem = data;

		if (!GetDevice()->CreateBuffer(mIndexBuffer.GetAddressOf(), &mIBDesc, &sub))
			return false;

		return true;
	}
	void Mesh::BindBuffer()
	{
		UINT stride = sizeof(renderer::Vertex);
		UINT offset = 0;

		GetDevice()->BindVertexBuffer(0, mVertexBuffer.GetAddressOf(), &stride, &offset);
		GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
	void Mesh::Render()
	{
		GetDevice()->DrawIndexed(mIndexCount, 0, 0);
	}
}