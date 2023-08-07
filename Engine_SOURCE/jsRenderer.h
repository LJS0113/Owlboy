#pragma once
#include "jsEngine.h"
#include "jsGraphicDevice_DX11.h"
#include "jsMesh.h"
#include "jsShader.h"
#include "jsConstantBuffer.h"
#include "jsCamera.h"
#include "jsLight.h"


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

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
		UINT animationType;
	};

	CBUFFER(SpriteReverseCB, CBSLOT_SPRITEREVERSE)
	{
		UINT reverse;
	};

	CBUFFER(ParticleCB, CBSLOT_PARTICLE)
	{
		UINT elementCount;
		float elapsedTime;
		int padd;
		int padd2;
	};

	extern js::Mesh* mesh;
	extern js::Shader* shader;
	extern js::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<js::Light*> lights;
	extern js::Camera* mainCamera;
	extern std::vector<js::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void BindLights();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh mesh);
}