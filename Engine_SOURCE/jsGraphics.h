#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include "jsEnums.h"
#include "jsMath.h"


#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 

#define CBSLOT_TRANSFORM		0
#define CBSLOT_GRID				2
//#define CBSLOT_PARTICLE			1

namespace js::graphics
{
	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		End,
	};

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		End,
	};
	
	enum class eSamplerType
	{
		Point,
		Anisotropic,
		End,
	};

	enum class eRSType
	{
		SolidBack,
		SolidFront,
		SolidNone,
		WireframeNone,
		End,
	};

	enum class eDSType
	{
		Less,
		Greater,
		NoWrite,
		None,
		End,
	};

	enum class eBSType
	{
		Default,
		AlphaBlend,
		OneOne,
		End,
	};

	enum class eRenderingMode
	{
		Opqque,
		CutOut,
		Transparent,
		End,
	};
	
	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GpuBuffer()
			: buffer(nullptr)
			, desc{}
		{

		}
		virtual ~GpuBuffer() = default;
	};

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;

		float raduis;
		float duration;
		float time;
	};

}