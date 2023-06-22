#pragma once
#include "jsEngine.h"
#include "jsGraphicDevice_DX11.h"
#include "jsMesh.h"
#include "jsShader.h"
#include "jsConstantBuffer.h"


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

	extern Vertex vertexes[];
	extern js::Mesh* mesh;
	extern js::Shader* shader;
	extern js::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	void Initialize();
	void Release();
}