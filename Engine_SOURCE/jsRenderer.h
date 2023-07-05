#pragma once
#include "jsEngine.h"
#include "jsGraphicDevice_DX11.h"
#include "jsMesh.h"
#include "jsShader.h"
#include "jsConstantBuffer.h"
#include "jsCamera.h"

using namespace js::math;
using namespace js::graphics;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	extern Vertex vertexes[];
	extern js::Mesh* mesh;
	extern js::Shader* shader;
	extern js::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<js::Camera*> cameras;

	void Initialize();
	void Render();
	void Release();
}