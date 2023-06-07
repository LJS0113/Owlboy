#pragma once
#include "jsEngine.h"
#include "jsGraphicDevice_DX11.h"
#include "jsMesh.h"
#include "jsShader.h"


using namespace js::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[];
	extern ID3D11InputLayout* triangleLayout;
	extern js::Mesh* mesh;
	extern ID3D11Buffer* triangleConstantBuffer;
	extern ID3DBlob* errorBlob;
	extern js::Shader* shader;
	extern ID3D11PixelShader* trianglePSShader;

	void Initialize();
	void Release();
}